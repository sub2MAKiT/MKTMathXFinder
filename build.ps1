param (
    [switch]$DEBUG = $false,
    [switch]$fast = $false
)
if ($DEBUG) {
    $DEBUGS = "-D_MKTDEBUGBOOL"
} else {
    $DEBUGS = ""
}

gcc $DEBUGS ./src/finder.c $(If ($fast) {"-Ofast"} Else {""}) -o MKT.exe