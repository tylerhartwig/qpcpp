//.$file${.::history.cpp} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: history.qm
// File:  ${.::history.cpp}
//
// This code has been generated by QM 5.1.0 <www.state-machine.com/qm/>.
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// This code is covered by the following QP license:
// License #   : QPCPP-EVAL
// Issued to   : Institution or an individual evaluating the QP/C++ framework
// Framework(s): qpcpp
// Support ends: 2021-12-31
// Product(s)  :
// This license is available only for evaluation purposes and
// the generated code is still licensed under the terms of GPL.
// Please submit request for extension of the evaluaion period at:
// <www.state-machine.com/licensing/#RequestForm>
//
//.$endhead${.::history.cpp} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#include "qpcpp.hpp"
#include "history.hpp"

#include "safe_std.h"   // portable "safe" <stdio.h>/<string.h> facilities
#include <stdlib.h>

Q_DEFINE_THIS_FILE

//.$declare${SMs::ToastOven} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//.${SMs::ToastOven} .........................................................
class ToastOven : public QP::QMsm {
public:
    ToastOven();

protected:
    QM_STATE_DECL( initial);
    QM_STATE_DECL( doorClosed);
    QM_ACTION_DECL(doorClosed_e);
    QM_ACTION_DECL(doorClosed_x);
    QM_ACTION_DECL(doorClosed_i);
    QM_STATE_DECL( heating);
    QM_ACTION_DECL(heating_e);
    QM_ACTION_DECL(heating_x);
    QM_ACTION_DECL(heating_i);
    QM_STATE_DECL( toasting);
    QM_ACTION_DECL(toasting_e);
    QM_STATE_DECL( baking);
    QM_ACTION_DECL(baking_e);
    QM_STATE_DECL( off);
    QM_ACTION_DECL(off_e);
    QM_STATE_DECL( doorOpen);
    QM_ACTION_DECL(doorOpen_e);
    QM_ACTION_DECL(doorOpen_x);
    QM_STATE_DECL( final);
    QM_ACTION_DECL(final_e);

protected:
    QP::QMState const *hist_doorClosed;
};
//.$enddecl${SMs::ToastOven} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

static ToastOven l_oven; // the only instance of the ToastOven class

// global-scope definitions ------------------------------------
QP::QMsm * const the_oven = &l_oven; // the opaque pointer

//.$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//. Check for the minimum required QP version
#if (QP_VERSION < 680U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpcpp version 6.8.0 or higher required
#endif
//.$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//.$define${SMs::ToastOven} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//.${SMs::ToastOven} .........................................................
//.${SMs::ToastOven::ToastOven} ..............................................
ToastOven::ToastOven()
 : QMsm(Q_STATE_CAST(&ToastOven::initial))
{}

//.${SMs::ToastOven::SM} .....................................................
QM_STATE_DEF(ToastOven, initial) {
    //.${SMs::ToastOven::SM::initial}
    (void)e; /* avoid compiler warning */
    // state history attributes
    hist_doorClosed = &off_s;

    QS_FUN_DICTIONARY(&ToastOven::doorClosed);
    QS_FUN_DICTIONARY(&ToastOven::heating);
    QS_FUN_DICTIONARY(&ToastOven::toasting);
    QS_FUN_DICTIONARY(&ToastOven::baking);
    QS_FUN_DICTIONARY(&ToastOven::off);
    QS_FUN_DICTIONARY(&ToastOven::doorOpen);
    QS_FUN_DICTIONARY(&ToastOven::final);

    static struct {
        QP::QMState const *target;
        QP::QActionHandler act[3];
    } const tatbl_ = { // tran-action table
        &doorClosed_s, // target state
        {
            &doorClosed_e, // entry
            &doorClosed_i, // initial tran.
            Q_ACTION_NULL // zero terminator
        }
    };
    return qm_tran_init(&tatbl_);
}
//.${SMs::ToastOven::SM::doorClosed} .........................................
QP::QMState const ToastOven::doorClosed_s = {
    QM_STATE_NULL, // superstate (top)
    &ToastOven::doorClosed,
    &ToastOven::doorClosed_e,
    &ToastOven::doorClosed_x,
    &ToastOven::doorClosed_i
};
//.${SMs::ToastOven::SM::doorClosed}
QM_ACTION_DEF(ToastOven, doorClosed_e) {
    PRINTF_S("%s;", "door-Closed");
    return qm_entry(&doorClosed_s);
}
//.${SMs::ToastOven::SM::doorClosed}
QM_ACTION_DEF(ToastOven, doorClosed_x) {
    // save deep history
    hist_doorClosed = stateObj();
    return qm_exit(&doorClosed_s);
}
//.${SMs::ToastOven::SM::doorClosed::initial}
QM_ACTION_DEF(ToastOven, doorClosed_i) {
    //.${SMs::ToastOven::SM::doorClosed::initial}

    static struct {
        QP::QMState const *target;
        QP::QActionHandler act[2];
    } const tatbl_ = { // tran-action table
        &off_s, // target state
        {
            &off_e, // entry
            Q_ACTION_NULL // zero terminator
        }
    };
    return qm_tran_init(&tatbl_);
}
//.${SMs::ToastOven::SM::doorClosed}
QM_STATE_DEF(ToastOven, doorClosed) {
    QP::QState status_;
    switch (e->sig) {
        //.${SMs::ToastOven::SM::doorClosed::TERMINATE}
        case TERMINATE_SIG: {

            static struct {
                QP::QMState const *target;
                QP::QActionHandler act[3];
            } const tatbl_ = { // tran-action table
                &final_s, // target state
                {
                    &doorClosed_x, // exit
                    &final_e, // entry
                    Q_ACTION_NULL // zero terminator
                }
            };
            status_ = qm_tran(&tatbl_);
            break;
        }
        //.${SMs::ToastOven::SM::doorClosed::OPEN}
        case OPEN_SIG: {

            static struct {
                QP::QMState const *target;
                QP::QActionHandler act[3];
            } const tatbl_ = { // tran-action table
                &doorOpen_s, // target state
                {
                    &doorClosed_x, // exit
                    &doorOpen_e, // entry
                    Q_ACTION_NULL // zero terminator
                }
            };
            status_ = qm_tran(&tatbl_);
            break;
        }
        //.${SMs::ToastOven::SM::doorClosed::TOAST}
        case TOAST_SIG: {

            static struct {
                QP::QMState const *target;
                QP::QActionHandler act[3];
            } const tatbl_ = { // tran-action table
                &toasting_s, // target state
                {
                    &heating_e, // entry
                    &toasting_e, // entry
                    Q_ACTION_NULL // zero terminator
                }
            };
            status_ = qm_tran(&tatbl_);
            break;
        }
        //.${SMs::ToastOven::SM::doorClosed::BAKE}
        case BAKE_SIG: {

            static struct {
                QP::QMState const *target;
                QP::QActionHandler act[3];
            } const tatbl_ = { // tran-action table
                &baking_s, // target state
                {
                    &heating_e, // entry
                    &baking_e, // entry
                    Q_ACTION_NULL // zero terminator
                }
            };
            status_ = qm_tran(&tatbl_);
            break;
        }
        //.${SMs::ToastOven::SM::doorClosed::OFF}
        case OFF_SIG: {

            static struct {
                QP::QMState const *target;
                QP::QActionHandler act[2];
            } const tatbl_ = { // tran-action table
                &off_s, // target state
                {
                    &off_e, // entry
                    Q_ACTION_NULL // zero terminator
                }
            };
            status_ = qm_tran(&tatbl_);
            break;
        }
        default: {
            status_ = Q_RET_SUPER;
            break;
        }
    }
    return status_;
}
//.${SMs::ToastOven::SM::doorClosed::heating} ................................
QP::QMState const ToastOven::heating_s = {
    &ToastOven::doorClosed_s, // superstate
    &ToastOven::heating,
    &ToastOven::heating_e,
    &ToastOven::heating_x,
    &ToastOven::heating_i
};
//.${SMs::ToastOven::SM::doorClosed::heating}
QM_ACTION_DEF(ToastOven, heating_e) {
    PRINTF_S("%s;", "heater-On");
    return qm_entry(&heating_s);
}
//.${SMs::ToastOven::SM::doorClosed::heating}
QM_ACTION_DEF(ToastOven, heating_x) {
    PRINTF_S("%s;", "heater-Off");
    return qm_exit(&heating_s);
}
//.${SMs::ToastOven::SM::doorClosed::heating::initial}
QM_ACTION_DEF(ToastOven, heating_i) {
    //.${SMs::ToastOven::SM::doorClosed::heating::initial}

    static struct {
        QP::QMState const *target;
        QP::QActionHandler act[2];
    } const tatbl_ = { // tran-action table
        &toasting_s, // target state
        {
            &toasting_e, // entry
            Q_ACTION_NULL // zero terminator
        }
    };
    return qm_tran_init(&tatbl_);
}
//.${SMs::ToastOven::SM::doorClosed::heating}
QM_STATE_DEF(ToastOven, heating) {
    QP::QState status_;
    switch (e->sig) {
        default: {
            status_ = Q_RET_SUPER;
            break;
        }
    }
    return status_;
}
//.${SMs::ToastOven::SM::doorClosed::heating::toasting} ......................
QP::QMState const ToastOven::toasting_s = {
    &ToastOven::heating_s, // superstate
    &ToastOven::toasting,
    &ToastOven::toasting_e,
    Q_ACTION_NULL, // no exit action
    Q_ACTION_NULL  // no initial tran.
};
//.${SMs::ToastOven::SM::doorClosed::heating::toasting}
QM_ACTION_DEF(ToastOven, toasting_e) {
    PRINTF_S("%s;", "toasting");
    return qm_entry(&toasting_s);
}
//.${SMs::ToastOven::SM::doorClosed::heating::toasting}
QM_STATE_DEF(ToastOven, toasting) {
    QP::QState status_;
    switch (e->sig) {
        default: {
            status_ = Q_RET_SUPER;
            break;
        }
    }
    return status_;
}
//.${SMs::ToastOven::SM::doorClosed::heating::baking} ........................
QP::QMState const ToastOven::baking_s = {
    &ToastOven::heating_s, // superstate
    &ToastOven::baking,
    &ToastOven::baking_e,
    Q_ACTION_NULL, // no exit action
    Q_ACTION_NULL  // no initial tran.
};
//.${SMs::ToastOven::SM::doorClosed::heating::baking}
QM_ACTION_DEF(ToastOven, baking_e) {
    PRINTF_S("%s;", "baking");
    return qm_entry(&baking_s);
}
//.${SMs::ToastOven::SM::doorClosed::heating::baking}
QM_STATE_DEF(ToastOven, baking) {
    QP::QState status_;
    switch (e->sig) {
        default: {
            status_ = Q_RET_SUPER;
            break;
        }
    }
    return status_;
}
//.${SMs::ToastOven::SM::doorClosed::off} ....................................
QP::QMState const ToastOven::off_s = {
    &ToastOven::doorClosed_s, // superstate
    &ToastOven::off,
    &ToastOven::off_e,
    Q_ACTION_NULL, // no exit action
    Q_ACTION_NULL  // no initial tran.
};
//.${SMs::ToastOven::SM::doorClosed::off}
QM_ACTION_DEF(ToastOven, off_e) {
    PRINTF_S("%s;", "toaster-Off");
    return qm_entry(&off_s);
}
//.${SMs::ToastOven::SM::doorClosed::off}
QM_STATE_DEF(ToastOven, off) {
    QP::QState status_;
    switch (e->sig) {
        default: {
            status_ = Q_RET_SUPER;
            break;
        }
    }
    return status_;
}
//.${SMs::ToastOven::SM::doorOpen} ...........................................
QP::QMState const ToastOven::doorOpen_s = {
    QM_STATE_NULL, // superstate (top)
    &ToastOven::doorOpen,
    &ToastOven::doorOpen_e,
    &ToastOven::doorOpen_x,
    Q_ACTION_NULL  // no initial tran.
};
//.${SMs::ToastOven::SM::doorOpen}
QM_ACTION_DEF(ToastOven, doorOpen_e) {
    PRINTF_S("%s;", "door-Open,lamp-On");
    return qm_entry(&doorOpen_s);
}
//.${SMs::ToastOven::SM::doorOpen}
QM_ACTION_DEF(ToastOven, doorOpen_x) {
    PRINTF_S("%s;", "lamp-Off");
    return qm_exit(&doorOpen_s);
}
//.${SMs::ToastOven::SM::doorOpen}
QM_STATE_DEF(ToastOven, doorOpen) {
    QP::QState status_;
    switch (e->sig) {
        //.${SMs::ToastOven::SM::doorOpen::CLOSE}
        case CLOSE_SIG: {

            static struct {
                QP::QMState const *target;
                QP::QActionHandler act[3];
            } const tatbl_ = { // tran-action table
                &doorClosed_s, // target state
                {
                    &doorOpen_x, // exit
                    &doorClosed_e, // entry
                    Q_ACTION_NULL // zero terminator
                }
            };
            status_ = qm_tran_hist(hist_doorClosed, &tatbl_);
            break;
        }
        //.${SMs::ToastOven::SM::doorOpen::TERMINATE}
        case TERMINATE_SIG: {

            static struct {
                QP::QMState const *target;
                QP::QActionHandler act[3];
            } const tatbl_ = { // tran-action table
                &final_s, // target state
                {
                    &doorOpen_x, // exit
                    &final_e, // entry
                    Q_ACTION_NULL // zero terminator
                }
            };
            status_ = qm_tran(&tatbl_);
            break;
        }
        default: {
            status_ = Q_RET_SUPER;
            break;
        }
    }
    return status_;
}
//.${SMs::ToastOven::SM::final} ..............................................
QP::QMState const ToastOven::final_s = {
    QM_STATE_NULL, // superstate (top)
    &ToastOven::final,
    &ToastOven::final_e,
    Q_ACTION_NULL, // no exit action
    Q_ACTION_NULL  // no initial tran.
};
//.${SMs::ToastOven::SM::final}
QM_ACTION_DEF(ToastOven, final_e) {
    PRINTF_S("%s\n", "-> final\nBye!Bye!");
    QP::QF::onCleanup();
    exit(0);
    return qm_entry(&final_s);
}
//.${SMs::ToastOven::SM::final}
QM_STATE_DEF(ToastOven, final) {
    QP::QState status_;
    switch (e->sig) {
        default: {
            status_ = Q_RET_SUPER;
            break;
        }
    }
    return status_;
}
//.$enddef${SMs::ToastOven} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
