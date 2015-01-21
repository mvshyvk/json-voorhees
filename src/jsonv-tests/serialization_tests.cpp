/** \file
 *  
 *  Copyright (c) 2015 by Travis Gockel. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it under the terms of the Apache License
 *  as published by the Apache Software Foundation, either version 2 of the License, or (at your option) any later
 *  version.
 *
 *  \author Travis Gockel (travis@gockelhut.com)
**/
#include "test.hpp"

#include <jsonv/parse.hpp>
#include <jsonv/serialization.hpp>
#include <jsonv/value.hpp>

#include <tuple>
#include <utility>

namespace jsonv_test
{

using namespace jsonv;

namespace
{

struct unassociated { };

struct my_thing
{
    int a;
    int b;
    std::string c;
    
    my_thing(const value& from, const extraction_context& cxt) :
            a(cxt.extract_sub<int>(from, "a")),
            b(cxt.extract_sub<int>(from, "b")),
            c(cxt.extract_sub<std::string>(from, "c"))
    { }
    
    my_thing(int a, int b, std::string c) :
            a(a),
            b(b),
            c(std::move(c))
    { }
    
    static const extractor* get_extractor()
    {
        static extractor_construction<my_thing> instance;
        return &instance;
    }
    
    bool operator==(const my_thing& other) const
    {
        return std::tie(a, b, c) == std::tie(other.a, other.b, other.c);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const my_thing& self)
    {
        return os << "{ a=" << self.a << ", b=" << self.b << ", c=" << self.c << " }";
    }
};

}

TEST(extract_basics)
{
    value val = parse(R"({
                        "i": 5,
                        "d": 4.5,
                        "s": "thing",
                        "a": [ 1, 2, 3 ],
                        "o": { "i": 5, "d": 4.5 }
                      })");
    extraction_context cxt(formats::defaults());
    ensure_eq(5, cxt.extract_sub<std::int8_t>(val, "i"));
    ensure_eq(5, cxt.extract_sub<std::uint8_t>(val, "i"));
    ensure_eq(5, cxt.extract_sub<std::int16_t>(val, "i"));
    ensure_eq(5, cxt.extract_sub<std::uint16_t>(val, "i"));
    ensure_eq(5, cxt.extract_sub<std::int32_t>(val, "i"));
    ensure_eq(5, cxt.extract_sub<std::uint32_t>(val, "i"));
    ensure_eq(5, cxt.extract_sub<std::int64_t>(val, "i"));
    ensure_eq(5, cxt.extract_sub<std::uint64_t>(val, "i"));
    ensure_eq(4.5f, cxt.extract_sub<float>(val, "d"));
    ensure_eq(4.5, cxt.extract_sub<double>(val, "d"));
    ensure_eq("thing", cxt.extract_sub<std::string>(val, "s"));
    ensure_throws(extraction_error, cxt.extract_sub<unassociated>(val, "o"));
    ensure_throws(extraction_error, cxt.extract_sub<int>(val, path::create(".a[3]")));
}

TEST(extract_object)
{
    formats fmts = formats::compose({ formats::defaults() });
    fmts.register_extractor(my_thing::get_extractor());
    
    my_thing res = extract<my_thing>(parse(R"({ "a": 1, "b": 2, "c": "thing" })"), fmts);
    ensure_eq(my_thing(1, 2, "thing"), res);
}

TEST(extract_object_search)
{
    formats base_fmts;
    base_fmts.register_extractor(my_thing::get_extractor());
    formats fmts = formats::compose({ formats::defaults(), base_fmts });
    
    my_thing res = extract<my_thing>(parse(R"({ "a": 1, "b": 2, "c": "thing" })"), fmts);
    ensure_eq(my_thing(1, 2, "thing"), res);
}

}
