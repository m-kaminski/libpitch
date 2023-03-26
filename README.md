# libpitch

library to parse Cboe equities TCP depth of book (PITCH) stream.

Implementation of specification from
https://cdn.cboe.com/resources/membership/Cboe_US_Equities_TCP_PITCH_Specification.pdf

# structure

```src/pitch/pitch.h``` includes main header for the library. Library is of header-only type,
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

## design

Library is implemented using C++ templates, in such a manner that messages are returned using preferred
smart pointer type of the user, or raw C-style pointer, however user prefers.

Each input line is supplied as pair of iterators, iterator type is templatized, so even raw C-style pointers
to a buffer can be used if your application performs I/O operations using low level C-style APIs

## format

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
