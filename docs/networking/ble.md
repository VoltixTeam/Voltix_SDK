(ble_driver)=
# Bluetooth Low Energy

Voltix has limited support for BLE. You can use the API to send advertisement packets with a custom payload on the three advertising channels.

The implementation is not standard-conformant. You may only use it for evaluation purposes in dedicated facilities where it cannot interfere with other spectrum users.

:::{important}
   Always check the return code of `voltix_ble_advertise(...)` to distinguish between a power failure (VOLTIX_ERR_RESET) and successful advertising (VOLTIX_SUCCESS).
:::


## Example usage

```{eval-rst}
.. literalinclude:: ../../examples/ble/src/main.c
   :language: c
   :linenos:
```

## API reference

```{eval-rst}
.. doxygengroup:: ble
   :project: voltix
   :content-only:
```