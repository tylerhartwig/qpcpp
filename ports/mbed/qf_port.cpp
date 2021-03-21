//
// Created by Tyler Hartwig on 3/8/21.
//

#define QP_IMPL
#include "qf_port.hpp"
#include "qf_pkg.hpp"
#include "qassert.h"
#include <chrono>
#ifdef Q_SPY
#include "qs_port.hpp"
#else
#include "qs_dummy.hpp"
#endif

using namespace std::chrono_literals;

namespace QP {
    Q_DEFINE_THIS_MODULE("qf_port")

    static bool is_running = false;
    static rtos::Mutex startup_mutex;
    static rtos::Mutex termination_mutex;
    static std::chrono::microseconds tick_period = 100ms;
    mbed::Ticker ticker;

    void QF::init(void) {
        startup_mutex.lock();
        termination_mutex.lock();

        extern uint_fast8_t QF_maxPool_;
        QF_maxPool_ = static_cast<uint_fast8_t>(0);
        bzero(&QF::timeEvtHead_[0], static_cast<uint_fast16_t>(sizeof(QF::timeEvtHead_)));
        bzero(&active_[0], static_cast<uint_fast16_t>(sizeof(active_)));
    }

    int_t QF::run(void) {

        printf("Starting up...\n");
        rtos::ThisThread::sleep_for(1000);
        onStartup();

        printf("Letting threads go\n");
        rtos::ThisThread::sleep_for(1000);
        startup_mutex.unlock();

        is_running = true;

        printf("Attaching clock tick\n");
        rtos::ThisThread::sleep_for(1000);
        ticker.attach(QF_onClockTick, tick_period);

        printf("Locking main on mutex\n");
        rtos::ThisThread::sleep_for(1000);
        termination_mutex.lock();

        printf("Cleaning up now!\n");
        rtos::ThisThread::sleep_for(1000);
        onCleanup();

        return static_cast<int_t>(0);
    }

    void QF_setTickRate(uint32_t ticksPerSec) {
        Q_REQUIRE_ID(300, ticksPerSec != static_cast<uint32_t>(0));
        tick_period = (1s / ticksPerSec);
    }

    void QF::stop(void) {
        if (!is_running) {
            return;
        }

        is_running = false;
        ticker.detach();
    }

    void QF::thread_(QActive* act) {
        while(is_running) {
            QEvt const* e = act->get_();
            act->dispatch(e, act->m_prio);
            gc(e);
        }
    }

    static void ao_thread(QActive* arg) {
        startup_mutex.lock();
        startup_mutex.unlock();

        auto act = reinterpret_cast<QActive*>(arg);

        QF::thread_(act);
        QF::remove_(act);
    }

    void QActive::start(uint_fast8_t prio,
                        QEvt const** qSto,
                        uint_fast16_t qLen,
                        void* const stkSto,
                        uint_fast16_t stkSize,
                        void const* ie) {
        m_eQueue.init(qSto, qLen);
        m_prio = static_cast<uint8_t>(prio);
        QF::add_(this);
        printf("starting init Hsm\n");
        this->init(ie, prio);

        printf("creating thread\n");
        m_thread = new rtos::Thread(
                static_cast<osPriority>(osPriorityNormal - 1 + prio),
                (stkSize != 0) ? static_cast<uint32_t>(stkSize) : OS_STACK_SIZE,
                static_cast<unsigned char *>(stkSto),
                "qpcpp thread");
        printf("Starting thread\n");
        m_thread->start(mbed::callback(&ao_thread, this));
        m_osObject = prio;
//        m_osObject = new rtos::EventFlags();
    }

    void QActive::stop(void) {
        unsubscribeAll();
//        delete m_osObject;
        m_thread->terminate();

        termination_mutex.unlock();
    }
}