
## 🔧 Solutions for Common Issues

### 🛠️ GTSAM Shared Library Error

**Error Message:**
```bash
error while loading shared libraries: libgtsam.so.4: cannot open shared object file: No such file or directory
````

**Cause:**
This error occurs when the system cannot locate the `libgtsam.so.4` shared library, usually because it's not properly installed or not in the system's library search path.

**Solution:**

1. **Ensure GTSAM is Installed Properly**
   Navigate to the GTSAM build directory and install it:

   ```bash
   cd /root/gtsam/build
   sudo make install
   ```

2. **Update Library Search Path**
   Add the GTSAM library path to your `LD_LIBRARY_PATH` environment variable:

   ```bash
   export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
   ```

   > ✅ *Tip:* To make this permanent, add the above line to your `~/.bashrc` or Dockerfile.


```
