#!/bin/bash

#=============#
#  CONSTANTS  #
#=============#
LIBNAME="libinstost.so"


#=============#
#  FUNCTIONS  #
#=============#
print_help() {
    echo -e "\
Tost injector usage:
  ${0} [load|reload|unload|help (\e[32mdefault\e[0m)]
"
}

is_injected() {
    grep -q "$LIBNAME" "/proc/$(pidof insurgency_linux)/maps"
    return $?
}

load() {
    sudo gdb -n -q -batch                                    \
        -ex "attach ${INS_PID}"                              \
        -ex "set \$dlopen = (void *(*)(char *, int)) dlopen" \
        -ex "set \$dlerror = (char *(*)(void)) dlerror"      \
        -ex "call \$dlopen(\"$(pwd)/build/${LIBNAME}\", 1)"  \
        -ex "call \$dlerror()"                               \
        -ex "detach"                                         \
        -ex "quit"
}

unload() {
    sudo gdb -n -q -batch                                              \
        -ex "attach ${INS_PID}"                                        \
        -ex "set \$dlopen = (void*(*)(char*, int)) dlopen"             \
        -ex "set \$dlclose = (int(*)(void*)) dlclose"                  \
        -ex "set \$library = \$dlopen(\"$(pwd)/build/${LIBNAME}\", 6)" \
        -ex "call \$dlclose(\$library)"                                \
        -ex "call \$dlclose(\$library)"                                \
        -ex "detach"                                                   \
        -ex "quit"
}

reload() {
    unload
    load
}


#=========#
#  ENTRY  #
#=========#
INS_PID=$(pidof insurgency_linux)
if [ -n  "$INS_PID" ]; then
    echo -e "Insurgency PID: \e[32m${INS_PID}\e[0m"
else
    echo -e "\e[31mInsurgency PID not found...\e[0m"
    exit 1
fi

LD_ACT=${1:-help}

case $LD_ACT in
    load)
        if is_injected; then
            echo -e "Already injected! \e[33mReloading...\e[0m"
            reload
        else
            load
        fi

        exit 0
        ;;

    reload)
        if is_injected; then
            reload
        else
            echo -e "Not yet injected! \e[33mLoading...\e[0m"
            load
        fi

        exit 0
        ;;

    unload)
        if is_injected; then
            unload
        else
            echo -e "Not yet injected!"
            exit 3
        fi

        exit 0
        ;;

    help)
        print_help
        exit 0
        ;;

    *)
        echo -e "Unknown command: \e[31m${LD_ACT}\e[0m"
        exit 2
        ;;
esac
