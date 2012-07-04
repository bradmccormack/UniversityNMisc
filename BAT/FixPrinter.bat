@ECHO OFF
REM Fix Spooler Problem

Echo Stopping Print Spool Service

REM make sure the Print spooler service is not running
Net Stop "Print Spooler"

Echo Clearing Spool Queue

REM now to delete all of the dodgy entries stuck in the spool queue
del C:\Windows\system32\spool\Printers\*.* /F/Q


REM now restart the Print spooler service 
Echo Starting Print Spooler service
Net Start "Print Spooler"

REM Hopefully all the junk stuck in the Spool directory is gone and all is good

Echo Please let Brad know if this does not fix your printer problem.
Pause

