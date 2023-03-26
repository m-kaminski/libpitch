# libpitch

library to parse Cboe equities TCP depth of book (PITCH) stream.

Implementation of specification from
https://cdn.cboe.com/resources/membership/Cboe_US_Equities_TCP_PITCH_Specification.pdf

# Structure

```src/include/pitch/pitch.h``` includes main header for the library. Library is of header-only type,
so nothing has to be compiled before including it in our program

at core of library there are two classes:

* ```pitch::decoder``` class implementing parsing process; Member function ```decode_message``` generates a
     smart pointer to a ```message``` type object
* ```pitch::messages::message``` class and its derived classes representing all the kinds of messages
    * ```pitch::messages::message::message_type``` enum to represent types of messages, names correspond to
              names of child classes of the ```message```

In addition there are following classes to represent distinct types of messages generated in Cboe PITCH stream:
* ```pitch::messages::symbol_clear```
* ```pitch::messages::add_order```
* ```pitch::messages::order_executed```
* ```pitch::messages::order_cancel```
* ```pitch::messages::trade```
* ```pitch::messages::trade_break```
* ```pitch::messages::trading_status```
* ```pitch::messages::auction_update```
* ```pitch::messages::auction_summary```
* ```pitch::messages::retail_price_improvement```

Every single one of these messages has getter methods corresponding to fields in PITCH message stream

## Design

Library is implemented using C++ templates, in such a manner that messages are returned using preferred
smart pointer type of the user, or raw C-style pointer, however user prefers.

Each input line is supplied as pair of iterators, iterator type is templatized, so even raw C-style pointers
to a buffer can be used if your application performs I/O operations using low level C-style APIs.

Library implements builder design pattern, whereas there is builder for each message type, invoked from "main"
builder in ```pitch::decoder::decode_message``` (in pitch/pitch.h). 

## Format

TCP depth of book (PITCH) stream is stream of text messages representing market event, including addition
execution and removal of trades.

Basic data types handled (through ranges) 
1. Alpha A string of ASCII letters (A-Z) left justified and space padded on the right.
2. Base 36 Numeric - 64 bit
3. Numeric (base 10) - 64 bit
4. Price (also base 10 numeric, 6 whole number digits + 4 digits for fraction of a dollar)
5. Printable ascii - string of printable ascii characters in 0x20 – 0x7e range
6. Timestamp - base 10 numeric - milliseconds past midnight eastern time

Take a closer look at following messages:

```29000020AA000ABDDCF0XS000300AMD   0000213700Y```

Above line line will be decoded as "add" (single character at offset 8).

```[29000020][A][A000ABDDCF0X][S][000300][AMD   ][0000213700][Y]```

After determining it's an "add", we can determine offsets and lengths of each
field, which will allow us to decode it with following properties:
```
timestamp: 29000020
message_type: add_order
order_id: 1316217846817392657 ( A000ABDDCF0X in base 36 )
side: sell ('S')
shares: 300 (prefixed with 0s, so 000300)
symbol: AMD (padded with ' 's)
price: 21.37 (0000213700)
display: true ('Y')
```

Consider another example

```29000600EA000ABDDCF0X0000200000ZAB00091```

This is an order_execute type message ('E' at position 8)

```[29000600][E][A000ABDDCF0X][000020][0000ZAB00091]```

Following information will be decoded:

```
timestamp: 29000600
message_type: order_execute
order_id: 1316217846817392657 (A000ABDDCF0X in base 36) - same as above
shares: 20 (so order above still has 280 shares outstanding)
execution_id: 2765178694981 (ZAB00091 in base 36)
```

## Usage

Unit tests for message classes, located in ```src/unit_test/messages``` provide
decent examples of usage of library function. Please consider simple example below:

```
std::string line("29000020AA000ABDDCF0XS000300AMD   0000213700Y");
//[29000020][A][A000ABDDCF0X][S][000300][AMD   ][0000213700][Y]

pitch::decoder d;
auto p = d.decode_message(line.begin(), line.end());
        
// message type is defined for base class
EXPECT_EQ(p->get_type(), message::add_order);

// to access fields specific to add_order class, cast to add_order
add_order * a = dynamic_cast<add_order*>(p.get());
EXPECT_EQ(a->get_timestamp(), 29000020);
EXPECT_EQ(a->get_type(), message::add_order);
EXPECT_EQ(a->get_order_id(), 1316217846817392657LL);
EXPECT_EQ(a->get_side(), types::side_type::sell);
EXPECT_EQ(a->get_shares(), 300);
EXPECT_EQ(a->get_symbol(), "AMD");
EXPECT_EQ(a->get_price(), 213700);
```

In addition all the message classes have doxygen style comments and 
detailed tables of fields with references to specific pages of Cboe
PITCH format documentation.

# Developing

Following packages are essential to run and test libpitch in CentOS operating
system (in other operating systems similar libraries may be needed)
```
yum install g++ make cmake gtest gtest-devel gcov
```

Following include path configuration is not needed for build, but may
make it easier to edit if your source editor doesn't get it from
parsing CMakeLists
```
${workspaceFolder}/src/include
${workspaceFolder}/src/include/pitch
```

Unit tests are located in
```
src/unit_test/{path corresponding to src/include/pitch/}
```
