// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/fml/native_library.h"

#include <Windows.h>

#include "flutter/fml/platform/win/wstring_conversion.h"

namespace fml {

NativeLibrary::NativeLibrary(const char* path)
    : handle_(nullptr), close_handle_(true) {
  if (path == nullptr) {
    return;
  }

  handle_ = ::LoadLibrary(StringToWideString(path).c_str());
}

NativeLibrary::NativeLibrary(Handle handle, bool close_handle)
    : handle_(handle), close_handle_(close_handle) {}

NativeLibrary::~NativeLibrary() {
  if (handle_ != nullptr && close_handle_) {
    ::FreeLibrary(handle_);
  }
}

NativeLibrary::Handle NativeLibrary::GetHandle() const {
  return handle_;
}

fml::RefPtr<NativeLibrary> NativeLibrary::Create(const char* path) {
  auto library = fml::AdoptRef(new NativeLibrary(path));
  return library->GetHandle() != nullptr ? library : nullptr;
}

fml::RefPtr<NativeLibrary> NativeLibrary::CreateWithHandle(
    Handle handle,
    bool close_handle_when_done) {
  auto library =
      fml::AdoptRef(new NativeLibrary(handle, close_handle_when_done));
  return library->GetHandle() != nullptr ? library : nullptr;
}

fml::RefPtr<NativeLibrary> NativeLibrary::CreateForCurrentProcess() {
  return fml::AdoptRef(new NativeLibrary(::GetModuleHandle(nullptr), false));
}

const uint8_t* NativeLibrary::ResolveSymbol(const char* symbol) {
  if (symbol == nullptr || handle_ == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<const uint8_t*>(::GetProcAddress(handle_, symbol));
}

}  // namespace fml
