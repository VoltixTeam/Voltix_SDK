(timing)=
# Timing

Currently, the SDK only supports simple sleep/delay and timestamping functionality.

*voltix_sleepX(..)* functions put the system into a low power sleep mode for the specified number of ticks or milliseconds.
If the power supply fails while sleeping, the functions may return earlier than requested with a `VOLTIX_ERR_RESET` return code.

*voltix_delayX(..)* functions spin the CPU until the specified number of milli/microseconds has passed.
If the runtime suspends execution or the power supply fails while waiting, the remaining cycles are waited after execution resumes.

## API reference

```{eval-rst}
.. doxygengroup:: timing
   :project: voltix
   :content-only:
```