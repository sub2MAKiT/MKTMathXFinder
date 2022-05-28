param (
    [switch]$DEBUG = $false,
    [switch]$fast = $false
)
if ($DEBUG) {
    $DEBUGS = "-D_MKTDEBUGBOOL"
} else {
    $DEBUGS = ""
}
gcc $DEBUGS ./src/finder.c ./src/main.c ./src/parser.c ./src/convenience.c -I c:/sdk/ $(If ($fast) {"-Ofast"} Else {""}) -o ./build/MKT_W.exe