//===-- include/common/patterns/Builder.h ---------------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file defines the Builder class, that serves as a contract to
/// be fulfilled by all builders.
///
//===----------------------------------------------------------------------===//
#ifndef BUILDER_H
#define BUILDER_H

#include <memory>

namespace Pattern {

/// \class Builder
/// \brief Abstract class for implementors of the builder design pattern.
/// This class serves as a contract to builders, specifying which methods they
/// must provide.
/// \tparam T Type of class to build.
template<class T>
class Builder {
  public:
    /// Virtual deconstructor
    virtual ~Builder() {};

    /// This function will construct an object of this builders template type,
    /// and will return a unique pointer to this the object, so ownership
    /// may be transfered.
    /// \returns unique_ptr to the constructed object.  
    virtual std::unique_ptr<T> build() = 0;
};

} // namespace Pattern

#endif // BUILDER_H //
