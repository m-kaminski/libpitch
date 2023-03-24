# libpitch

library to parse Cboe equities TCP depth of book (PITCH) stream.

Implementation of specification from
https://cdn.cboe.com/resources/membership/Cboe_US_Equities_TCP_PITCH_Specification.pdf

Basic data types handled (through ranges) 
1. Alpha A string of ASCII letters (A-Z) left justified and space padded on the right.
2. Base 36 Numeric - 64 bit
3. Numeric (base 10) - 64 bit
4. Price (also base 10 numeric, 6 whole number digits + 4 digits for fraction of a dollar)
5. Printable ascii - string of printable ascii characters in 0x20 – 0x7e range
6. Timestamp - base 10 numeric - milliseconds past midnight eastern time
