//
// Created by Tyler Hartwig on 3/8/21.
//

#ifndef QF_PORT_HPP
#define QF_PORT_HPP

#define QF_ACTIVE_STOP
#define OS_STACKPTR
#define QF_EQUEUE_TYPE              QEQueue
#define QF_THREAD_TYPE              rtos::Thread*
#define QF_OS_OBJECT_TYPE           uint8_t

#define QF_MAX_ACTIVE               32U

#include "mbed/mbed.h"

#define QF_INT_DISABLE()        do { \
        mbed::CriticalSectionLock::enable();                         \
    } while(0)

#define QF_INT_ENABLE()          do { \
        mbed::CriticalSectionLock::disable();       \
    } while(0)

#undef QF_CRIT_STAT_TYPE
#define QF_CRIT_ENTRY(dummy)   QF_INT_DISABLE()
#define QF_CRIT_EXIT(dummy)    QF_INT_ENABLE()

#include "qep_port.hpp"
#include "qequeue.hpp"
#include "qmpool.hpp"
#include "qf.hpp"

namespace QP {
    void QF_setTickRate(uint32_t ticksPerSec);
    void QF_onClockTick(void);
    static rtos::EventFlags queue_flags;
}

#ifdef QP_IMPL

#define QACTIVE_EQUEUE_WAIT_(me_) \
    while ((me_)->m_eQueue.m_frontEvt == static_cast<QEvt*>(0)) { \
        QF_CRIT_EXIT(dummy);      \
        printf("locknig waiting for event\n");                          \
        QP::queue_flags.wait_all(1U << (me_)->m_osObject);        \
        printf("Got Flag, unlocked!\n");                          \
        QF_CRIT_ENTRY(dummy);                                  \
    }

#define QACTIVE_EQUEUE_SIGNAL_(me_) QP::queue_flags.set(1U << (me_)->m_osObject)

#define QF_SCHED_STAT_
#define QF_SCHED_LOCK_(dummy) ((void)0)
#define QF_SCHED_UNLOCK_() ((void)0)

#define QF_EPOOL_TYPE_ QMPool
#define QF_EPOOL_INIT_(p_, poolSto_, poolSize_, evtSize_) (p_).init((poolSto_), (poolSize_), (evtSize_))
#define QF_EPOOL_EVENT_SIZE_(p_) static_cast<uint_fast16_t>((p_).getBlockSize())
#define QF_EPOOL_GET_(p_, e_, m_, qs_id_) ((e_) = static_cast<QEvt*>((p_).get((m_), (qs_id_))))
#define QF_EPOOL_PUT_(p_, e_, qs_id_) ((p_).put((e_), (qs_id_)))

#endif // QP_IMPL


#endif // QF_PORT_HPP
