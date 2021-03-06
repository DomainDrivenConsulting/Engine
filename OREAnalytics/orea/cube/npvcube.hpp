/*
 Copyright (C) 2016 Quaternion Risk Management Ltd
 All rights reserved.

 This file is part of ORE, a free-software/open-source library
 for transparent pricing and risk analysis - http://opensourcerisk.org

 ORE is free software: you can redistribute it and/or modify it
 under the terms of the Modified BSD License.  You should have received a
 copy of the license along with this program.
 The license is also available online at <http://opensourcerisk.org>

 This program is distributed on the basis that it will form a useful
 contribution to risk analytics and model standardisation, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
*/

/*! \file orea/cube/npvcube.hpp
    \brief The base NPV cube class
    \ingroup cube
*/

#pragma once

#include <boost/shared_ptr.hpp>
#include <ql/time/date.hpp>
#include <ql/types.hpp>
#include <vector>

using QuantLib::Size;
using QuantLib::Real;

namespace ore {
namespace analytics {
//! NPV Cube class stores both future and current NPV values.
/*! The cube class stores futures NPV values in a 3-D array, i.e. each side can be of a different
 *  length (so a cuboid).
 *
 *  This abstract base class is just used for the storage of a cube.
 *  This class also stores the tradeIds, dates and vector of T0 NPVs
  \ingroup cube
 */
class NPVCube {
public:
    //! default ctor
    NPVCube() {}

    //! Do not allow cube copying
    NPVCube(NPVCube&) = delete;
    NPVCube& operator=(NPVCube const&) = delete;

    //! dtor
    virtual ~NPVCube() {}

    //! Return the length of each dimension
    virtual Size numIds() const = 0;
    virtual Size numDates() const = 0;
    virtual Size samples() const = 0;
    virtual Size depth() const = 0;

    //! Get the vector of ids for this cube
    virtual const std::vector<std::string>& ids() const = 0;
    //! Get the vector of dates for this cube
    virtual const std::vector<QuantLib::Date>& dates() const = 0; // TODO: Should this be the full date grid?

    //! Return the asof date (T0 date)
    virtual QuantLib::Date asof() const = 0;
    //! Get a T0 value from the cube
    virtual Real getT0(Size id, Size depth = 0) const = 0;
    //! Set a value in the cube
    virtual void setT0(Real value, Size id, Size depth = 0) = 0;

    //! Get a value from the cube
    virtual Real get(Size id, Size date, Size sample, Size depth = 0) const = 0;
    //! Set a value in the cube
    virtual void set(Real value, Size id, Size date, Size sample, Size depth = 0) = 0;

    //! Load cube contents from disk
    virtual void load(const std::string& fileName) = 0;
    //! Persist cube contents to disk
    virtual void save(const std::string& fileName) const = 0;
};
} // namespace analytics
} // namespace ore
