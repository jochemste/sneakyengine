# Display and video handling

This module is intended to get data to display, convert it to the format that can be displayed, buffer it, and finally display it.
This module is currently not implemented yet. As a first version, this will be implemented as a simple single threaded process, although the expectation is to switch to a event based or multi-threaded implementation.

## Sequence

1. Data provided to module
2. Data converted
3. Data buffered in queue
4. Data is retrieved from queue
5. Data is displayed

