//
// Created by guozhenxiong on 2021-11-21.
//

#include <jni.h>

#include "third_party/flutter/fml/logging.h"

// This is called by the VM when the shared library is first loaded.
JNIEXPORT jint
JNI_OnLoad(JavaVM
           *vm,
           void *reserved)
{
// Initialize the Java VM.
    FML_LOG(INFO) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxx";

    return JNI_VERSION_1_4;
}