---
layout: plain
generate: false
---
The width is an optional integer that specifies the minimum width of the field we use to print the value. If the value is smaller than the width the field is padded using the padding value (see Flags to change the padding value).

Note: If the value is larger than the specified width it will overflow the field (i.e. no cutting is done to truncate the value to the field width).

Example: `%15d`

