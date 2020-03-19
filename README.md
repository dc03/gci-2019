# Unit converter

This is my attempt at creating a functional unit converter that can read from
a user defined config file and catch any errors that occur

A configuration file is provided as - "conversion_table.txt"

## The format of the file is as follows

- A '#' at the start of any line indicates a comment
- A line starting with "base unit" specifies that a base unit is created
- A line starting with a name and then "can be" is used to specify alternate names for the unit
- A line starting with a number then a name is used to define the value of that unit in terms of the base unit

## The input format is as follows

### "value" "unit_from" to (or) as (or) from (or) in "unit_to", where:

- value: the amount to be converted
- unit_from: the unit to be converted from
- unit_to: the unit to be converted to
