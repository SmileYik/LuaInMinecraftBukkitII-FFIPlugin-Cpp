LuaInMinecraftBukkitII-FFIPlugin-Cpp
=====

This is a demo for LuaInMinecraftBukkitII. Outputed shared library can be load by ffi module.

## How to use

Clone this repository and make it at first.
Put `cffi.dll/cffi.so` to your `luaLibrary` folder, and put `ffi-plugin.dll` to `luaState` folder.

Create a lua script file like this:

```lua
local ffi = require("cffi")
ffi.cdef([[
    struct LuaBukkit {
        void* env;
        void* helper;
        void* io;
        void* bukkit;
        void* plugin;
        void* server;
        void* log;
        void* out;
    };

    void onEnable(void *jniEnv, struct LuaBukkit luaBukkit);

    void onDisable(void *jniEnv);
]])

-- -!! change ffi-plugin.dll to yours !!-
local plugin = ffi.load(luaBukkit.env:path("ffi-plugin.dll"))
plugin.onEnable(luajava.env(), ffi.new("struct LuaBukkit", luaBukkit))
```

Then launcher your server, you will saw something.