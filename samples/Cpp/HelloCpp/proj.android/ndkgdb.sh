APPNAME="HelloCpp"
APP_ANDROID_NAME="org.cocos2dx.hellocpp"

if [ -z "${ANDROID_SDK+aaa}" ]; then
    ANDROID_SDK="$HOME/bin/android-sdk"
fi

if [ -z "${NDK_ROOT+aaa}" ]; then
# ... if NDK_ROOT is not set, use "$HOME/bin/android-ndk"
    NDK_ROOT="$HOME/bin/android-ndk"
fi

if [ -z "${COCOS2DX_ROOT+aaa}" ]; then
# ... if COCOS2DX_ROOT is not set
# ... find current working directory
    DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory
    COCOS2DX_ROOT="$DIR/../../../.."
    APP_ROOT="$DIR/.."
    APP_ANDROID_ROOT="$DIR"
else
    APP_ROOT="$COCOS2DX_ROOT/samples/$APPNAME"
    APP_ANDROID_ROOT="$COCOS2DX_ROOT/samples/$APPNAME/proj.android"
fi

echo "NDK_ROOT = $NDK_ROOT"
echo "ANDROID_SDK = $ANDROID_SDK"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"
echo "APP_ANDROID_NAME = $APP_ANDROID_NAME"

echo
echo "Killing and restarting ${APP_ANDROID_NAME}"
echo

set -x

"${ANDROID_SDK}/platform-tools/adb shell am force-stop ${APP_ANDROID_NAME}"

NDK_MODULE_PATH="${COCOS2DX_ROOT}":"${COCOS2DX_ROOT}"/cocos2dx/platform/third_party/android/prebuilt \
    "${NDK_ROOT}"/ndk-gdb \
    --adb="${ANDROID_SDK}"/platform-tools/adb \
    --verbose \
    --start \
    --force
