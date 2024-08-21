# GetMaximizedScreenSize Function - README

## Overview

The `GetMaximizedScreenSize` function is designed to retrieve the screen size of a specified monitor in a Windows environment. The screen size obtained by this function includes the entire monitor area, not just the working area (i.e., it includes the taskbar and any other system-reserved areas). This function is particularly useful in applications where knowledge of the full screen dimensions of multiple monitors is necessary.

## Function Signature

```cpp
/**
 * @brief Retrieves the screen size of the specified monitor.
 * 
 * This function retrieves the size of the screen for a specified monitor index.
 * The size includes the full monitor area, not just the working area.
 * 
 * @param monitorIndex The index of the monitor to retrieve the size for.
 * @return RECT The screen size of the monitor.
 */
RECT GetMaximizedScreenSize(int monitorIndex);
```

## Parameters

- **`monitorIndex`**: This is an integer representing the index of the monitor for which the screen size is to be retrieved. Monitor indices are generally zero-based, meaning the primary monitor is usually at index 0, the first secondary monitor at index 1, and so on.

## Return Value

- **`RECT`**: This function returns a `RECT` structure containing the coordinates of the screen. The `RECT` structure includes four values:
  - `left`: The x-coordinate of the upper-left corner of the monitor.
  - `top`: The y-coordinate of the upper-left corner of the monitor.
  - `right`: The x-coordinate of the lower-right corner of the monitor.
  - `bottom`: The y-coordinate of the lower-right corner of the monitor.

The width of the screen can be calculated as `right - left`, and the height as `bottom - top`.

## How It Works

1. **Display Device Enumeration**:
   - The function begins by enumerating display devices using the `EnumDisplayDevices` function. This function iterates through all connected display devices (monitors) and checks if the current device matches the specified `monitorIndex`.
   - If the desired monitor is found (`deviceIndex == monitorIndex`), it proceeds to retrieve the screen size.
   - If the specified `monitorIndex` does not exist, the function outputs an error message and terminates the program.

2. **Monitor Handle Retrieval**:
   - The function obtains a handle to the monitor using `MonitorFromWindow`, which defaults to the primary monitor. This is currently a limitation since it doesn't correctly associate the handle with the monitor index.
   
3. **Monitor Information Retrieval**:
   - The `GetMonitorInfo` function is then used to retrieve information about the monitor. The function fills a `MONITORINFO` structure with details including the monitor’s work area and the full screen area.
   - The full screen area (`rcMonitor`) is extracted from the `MONITORINFO` structure and returned as the screen size.

4. **Error Handling**:
   - The function checks for potential errors at two key points: when enumerating devices and when retrieving monitor information. If any step fails, an error message is printed to `stderr`, and the program exits with a non-zero status.

## Limitations

- **Monitor Handle Mismatch**: The current implementation of the function obtains a monitor handle using `MonitorFromWindow` with `NULL` and `MONITOR_DEFAULTTOPRIMARY`. This approach always returns the primary monitor, which might not correspond to the `monitorIndex` specified by the user.
- **No Support for Multi-Monitor Setups**: While the function attempts to support multiple monitors, the limitation mentioned above means it will not correctly handle non-primary monitors.

## Potential Improvements

1. **Correct Monitor Handle Association**:
   - Modify the function to correctly associate the `monitorIndex` with the corresponding monitor handle instead of defaulting to the primary monitor.

2. **Enhanced Error Handling**:
   - Improve error handling by providing more descriptive messages and considering fallback strategies instead of terminating the program immediately.

3. **Multi-Monitor Setup**:
   - Enhance support for multi-monitor setups by correctly handling and returning screen sizes for the specified monitor index.

## Example Usage

```cpp
int main() {
    int monitorIndex = 1; // Assume we want to get the screen size for the second monitor
    RECT screenSize = GetMaximizedScreenSize(monitorIndex);

    std::cout << "Monitor " << monitorIndex << " Screen Size: "
              << "Width = " << (screenSize.right - screenSize.left)
              << ", Height = " << (screenSize.bottom - screenSize.top)
              << std::endl;

    return 0;
}
```

This example attempts to retrieve and print the screen size of the second monitor. Ensure that the monitor index provided is valid; otherwise, the function will terminate with an error.

## Conclusion

The `GetMaximizedScreenSize` function is a utility that facilitates retrieving the full screen size of a specified monitor. While it has its limitations, it provides a foundation for working with multi-monitor setups in Windows environments. Developers are encouraged to refine the function further to handle various edge cases and improve its robustness.
