
//
// This source file is part of appleseed.
// Visit https://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014-2018 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_FOUNDATION_PLATFORM_DATETIME_H
#define APPLESEED_FOUNDATION_PLATFORM_DATETIME_H

// appleseed.foundation headers.
#include "foundation/platform/types.h"
#include "foundation/utility/string.h"

// Boost headers.
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

// Standard headers.
#include <iterator>
#include <sstream>
#include <string>

namespace foundation
{

boost::posix_time::time_duration microseconds_to_time_duration(uint64 microseconds);

template <> std::string to_string(const boost::posix_time::ptime& time);
template <> std::string to_string(const boost::posix_time::time_duration& td);
template <> std::string to_string(const boost::gregorian::date& date);


//
// Implementation.
//

inline boost::posix_time::time_duration microseconds_to_time_duration(uint64 microseconds)
{
    using namespace boost::posix_time;

    uint64 seconds = microseconds / 1000000;
    microseconds -= seconds * 1000000;

    uint64 minutes = seconds / 60;
    seconds -= minutes * 60;

    uint64 hours = minutes / 60;
    minutes -= hours * 60;

    return
        time_duration(
            static_cast<time_duration::hour_type>(hours),
            static_cast<time_duration::min_type>(minutes),
            static_cast<time_duration::sec_type>(seconds),
            static_cast<time_duration::fractional_seconds_type>(microseconds));
}

template <>
inline std::string to_string(const boost::posix_time::ptime& time)
{
    return boost::posix_time::to_iso_string(time);
}

template <>
inline std::string to_string(const boost::posix_time::time_duration& td)
{
    std::stringstream sstr;
    std::ostreambuf_iterator<char> oitr(sstr);

    boost::posix_time::time_facet facet;
    facet.put(oitr, sstr, sstr.fill(), td);

    return sstr.str();
}

template <>
inline std::string to_string(const boost::gregorian::date& date)
{
    std::stringstream sstr;
    std::ostreambuf_iterator<char> oitr(sstr);

    boost::gregorian::date_facet facet;
    facet.put(oitr, sstr, sstr.fill(), date);

    return sstr.str();
}

}       // namespace foundation

#endif  // !APPLESEED_FOUNDATION_PLATFORM_DATETIME_H
