@echo off
setlocal EnableDelayedExpansion
set a = 1;
for %%n in (*.jfif) do (
set /A a+=1
ren "%%n" "!a!.jfif"
)
pause