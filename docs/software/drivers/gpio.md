# GPIO

The Voltix Module/Board has 11 digital GPIO pins.
The API allows configuring pins as input or output.
Outputs can be controlled similar to any other battery-powered device.
Inputs can always be read with `voltix_gpio_read(unsigned int pin)` or the application can wait for a specified level on the pin with `voltix_gpio_wait_level(...)`.

:::{important}
   Always check the return code of `voltix_gpio_wait_level(...)` to distinguish between a power failure (VOLTIX_ERR_RESET) and an actual level detection event (VOLTIX_SUCCESS).
:::

## Example usage

```{eval-rst}
.. literalinclude:: ../../../examples/gpio/src/main.c
   :language: c
   :linenos:
```

## API Reference

```{eval-rst}
.. doxygengroup:: gpio
   :project: voltix
   :content-only:
```