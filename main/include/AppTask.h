/*
 *
 *    Copyright (c) 2019 Google LLC.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef APP_TASK_H
#define APP_TASK_H

#include <stdint.h>
#include <stdbool.h>

#include "AppEvent.h"
#include "BoltLockManager.h"

#include <Weave/DeviceLayer/WeaveDeviceLayer.h>
#include <Weave/DeviceLayer/SoftwareUpdateManager.h>

class AppTask
{
    typedef ::nl::Weave::DeviceLayer::SoftwareUpdateManager SoftwareUpdateManager;

public:
    int StartAppTask();
    static void AppTaskMain(void * pvParameter);

    void PostEvent(const AppEvent * event);

private:
    friend AppTask & GetAppTask(void);

    int Init();

    void CancelTimer(void);

    void DispatchEvent(AppEvent * event);

    static void SeachForLocalSDKOpenCloseSensors(intptr_t arg);

    // Button Event Handlers
    static void FunctionButtonHandler(const AppEvent * aEvent);
    static void AttentionButtonHandler(const AppEvent * aEvent);

    // Other Event Handler
    static void LockActionEventHandler(const AppEvent * aEvent, intptr_t Arg);
    static void FactoryResetTriggerTimerExpired(const AppEvent * aEvent);
    static void InstallEventHandler(const AppEvent * aEvent);
    static void TimerEventHandler(void * p_context);

    static void HandleSoftwareUpdateEvent(void *apAppState,
                                          SoftwareUpdateManager::EventType aEvent,
                                          const SoftwareUpdateManager::InEventParam& aInParam,
                                          SoftwareUpdateManager::OutEventParam& aOutParam);


    void StartTimer(uint32_t aTimeoutInMs);

    enum Function_t
    {
        kFunction_NoneSelected   = 0,
        kFunction_SoftwareUpdate = 0,
        kFunction_FactoryReset,

        kFunction_Invalid
    } Function;

    bool mFactoryResetTimerActive;

    static AppTask sAppTask;
};

inline AppTask & GetAppTask(void)
{
    return AppTask::sAppTask;
}

#endif // APP_TASK_H