export R_HELPER_ROOT="/home/roger/Code/ACM/cl/"

function do_py() {
    python3 "$@";
}

function do_after() {
    source $R_HELPER_ROOT/scripts/end.sh
}

function sw() {
    do_py $R_HELPER_ROOT/scripts/py/switch.py "$@"
    do_after
}

function new() {
    do_py $R_HELPER_ROOT/scripts/py/new.py "$@"
    do_after
}

function w() {
    do_py $R_HELPER_ROOT/scripts/py/watch.py "$@"
#    do_after
}

function pre() {
    do_py $R_HELPER_ROOT/scripts/py/pre.py "$@"
#    do_after
}

function update_alias(){
    source $R_HELPER_ROOT/scripts/alias.sh
}

function add_cmake(){
    do_py $R_HELPER_ROOT/scripts/py/add_cmake.py "$@"
}

function b() {
    do_py $R_HELPER_ROOT/scripts/py/build.py "$@"
    do_after
}

function r() {
    do_py $R_HELPER_ROOT/scripts/py/judge.py "$@"
#    do_after
}

function add_test() {
    do_py $R_HELPER_ROOT/scripts/py/add_test.py "$@"
#    do_after
}

