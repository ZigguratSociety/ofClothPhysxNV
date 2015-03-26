# add custom variables to this file

# OF_ROOT allows to move projects outside apps/* just set this variable to the
# absoulte path to the OF root folder

OF_ROOT = ../../..

hpaths    = -I../physxNV/Include

lpaths    = -L../physxNV/Lib/linux64
lpaths    += -L../physxNV/lib/linux64
lpaths    += -L../physxNV/Bin/linux64
lpaths    += -L../physxNV/lib/linux64

defines   = -DPHYSX_PROFILE_SDK
defines   += -DRENDER_SNIPPET
defines   += -D_DEBUG
defines   += -DPX_DEBUG
defines   += -DPX_CHECKED
defines   += -DPX_SUPPORT_VISUAL_DEBUGGER

libraries = -lSnippetRenderDEBUG
libraries += -lSnippetUtilsDEBUG
libraries += -lPhysX3DEBUG_x64
libraries += -lPhysX3CommonDEBUG_x64
libraries += -lPhysX3CookingDEBUG_x64
libraries += -lPhysX3CharacterKinematicDEBUG_x64
libraries += -lPhysX3ExtensionsDEBUG
libraries += -lPhysX3VehicleDEBUG
libraries += -lPhysXProfileSDKDEBUG
libraries += -lPhysXVisualDebuggerSDKDEBUG
libraries += -lPxTaskDEBUG
libraries += -lSnippetUtilsDEBUG
libraries += -lSnippetRenderDEBUG
libraries += -lGL
libraries += -lGLU
libraries += -lglut
libraries += -lX11
libraries += -lrt
libraries += -lpthread

cflags = -MMD
cflags += $(defines)
cflags += $(hpaths)
cflags += -m64

cflags  += -m64 -fPIC -msse2 -mfpmath=sse -ffast-math -fexceptions -frtti -fvisibility=hidden -fvisibility-inlines-hidden
cflags  += -Wall -Wextra -fdiagnostics-show-option
cflags  += -Wno-long-long
cflags  += -Wno-unknown-pragmas -Wno-invalid-offsetof -Wno-uninitialized
cflags  += -Wno-unused-parameter
cflags  += -g3 -gdwarf-2

cppflags  += -m64 -fPIC -msse2 -mfpmath=sse -ffast-math -fexceptions -frtti -fvisibility=hidden -fvisibility-inlines-hidden
cppflags  += -Wall -Wextra -fdiagnostics-show-option
cppflags  += -Wno-long-long
cppflags  += -Wno-unknown-pragmas -Wno-invalid-offsetof -Wno-uninitialized
cppflags  += -Wno-unused-parameter
cppflags  += -g3 -gdwarf-2

lflags    += -L, $(lpaths)
lflags    += -Wl,--start-group $(libraries) -Wl,--end-group
lflags  += -lrt
lflags  += -m64

# USER_CFLAGS allows to pass custom flags to the compiler
# for example search paths like:
# USER_CFLAGS = -I src/objects

USER_CFLAGS = $(cflags) $(cppflags)


# USER_LDFLAGS allows to pass custom flags to the linker
# for example libraries like:
# USER_LDFLAGS = libs/libawesomelib.a

USER_LDFLAGS = $(defines) $(lflags)


EXCLUDE_FROM_SOURCE="bin,.xcodeproj,obj"

# change this to add different compiler optimizations to your project

USER_COMPILER_OPTIMIZATION = -march=native -mtune=native -Os


# android specific, in case you want to use different optimizations
USER_LIBS_ARM = 
USER_LIBS_ARM7 = 
USER_LIBS_NEON = 

# android optimizations

ANDROID_COMPILER_OPTIMIZATION = -Os

NDK_PLATFORM = android-8

# uncomment this for custom application name (if the folder name is different than the application name)
#APPNAME = folderName

# uncomment this for custom package name, must be the same as the java package that contains OFActivity
#PKGNAME = cc.openframeworks.$(APPNAME)





# linux arm flags

LINUX_ARM7_COMPILER_OPTIMIZATIONS = -march=armv7-a -mtune=cortex-a8 -finline-functions -funroll-all-loops  -O3 -funsafe-math-optimizations -mfpu=neon -ftree-vectorize -mfloat-abi=hard -mfpu=vfp



