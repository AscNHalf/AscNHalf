@ECHO off
COLOR 9
REM #####################################
REM #database									#
REM #####################################
:TOP
ECHO 	Welcome, in the AscNHalf project
ECHO.

set /p server=   			Server/Host: 
set /p user=   			Database login: 
set /p pass=   			Password: 
set /p cdb=   			Char Database: 
set /p ldb=   			Logon Database: 
set /p wdb=   			World Database: 
Set port=3306

if %user% == CHANGEME GOTO error
if %pass% == CHANGEME GOTO error
:menu
cls
ECHO.
ECHO               ###########################################
ECHO               #                 Updater                 #
ECHO               #                  install                #
ECHO               ###########################################
ECHO.
ECHO		   Please Select an Option:
ECHO.
ECHO               a = Install Char  updates
ECHO               b = Install Logon updates
ECHO               u = Install World updates
ECHO.
ECHO               x = Exit Installer
ECHO.
set /p l=		Enter Option: 
if %l%==* goto error
if %l%==a goto char
if %l%==A goto char
if %l%==b goto logon
if %l%==B goto logon
if %l%==u goto world
if %l%==U goto world
if %l%==x goto quit
if %l%==X goto quit

goto error

:char
CLS
ECHO.
ECHO [Import] Install Char updates Database...
ECHO [Import]
ECHO [Import] Install Update
for %%a in ("char_updates\*.sql") do mysql -h %server%  --user=%user% --password=%pass% --force %cdb% < %%a
ECHO.
ECHO Done!
PAUSE
GOTO MENU

:world
CLS
ECHO.
ECHO [Import] Install AscNHalf World Update...
ECHO [Import]
ECHO [Import] Install Updates
for %%a in ("world_updates\*.sql") do mysql -h %server%  --user=%user% --password=%pass% --force %wdb% < %%a
ECHO.
ECHO Done!
PAUSE
GOTO MENU

:logon
CLS
ECHO [Import] Install Logon Updates Database...
ECHO [Import]
ECHO [Import] Install Update
for %%a in ("logon_updates\*.sql") do mysql -h %server%  --user=%user% --password=%pass% --force %ldb% < %%a
ECHO.
ECHO Done!
PAUSE
GOTO MENU

:error
CLS
ECHO.
ECHO ! ERROR ! And Error has occured in your transaction! You will be returned to menu.
ECHO.
ECHO.
PAUSE
GOTO quit
:quit