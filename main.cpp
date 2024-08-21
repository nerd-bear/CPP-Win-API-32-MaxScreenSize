    /**
     * @brief Retrieves the screen size of the specified monitor.
     * 
     * This function retrieves the size of the screen for a specified monitor index.
     * The size includes the full monitor area, not just the working area.
     * 
     * @param monitorIndex The index of the monitor to retrieve the size for.
     * @return RECT The screen size of the monitor.
     */
    RECT GetMaximizedScreenSize(int monitorIndex) {
        DISPLAY_DEVICE dd = { sizeof(dd) };
        int deviceIndex = 0;
        bool monitorFound = false;
        RECT screenSize = {0, 0, 0, 0};

        // Enumerate display devices
        while (EnumDisplayDevices(NULL, deviceIndex, &dd, 0)) {
            if (deviceIndex == monitorIndex) {
                monitorFound = true;
                break;
            }
            deviceIndex++;
        }

        if (!monitorFound) {
            std::cerr << "Monitor index " << monitorIndex << " does not exist.\n";
            exit(1);
        }

        // Get the monitor info
        HMONITOR hMonitor = MonitorFromWindow(NULL, MONITOR_DEFAULTTOPRIMARY);
        MONITORINFO monitorInfo = {sizeof(MONITORINFO)};
        if (GetMonitorInfo(hMonitor, &monitorInfo)) {
            screenSize = monitorInfo.rcMonitor;  // Use rcMonitor instead of rcWork
        } else {
            std::cerr << "Failed to get monitor info.\n";
            exit(1);
        }

        return screenSize;
    }
