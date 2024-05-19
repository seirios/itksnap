cmake_minimum_required(VERSION 3.16)
SET(KEYCHAIN @SNAP_MACOS_KEYCHAIN@)
SET(PASSWORD_FILE @SNAP_MACOS_KEYCHAIN_PASSWORD_FILE@)

IF(KEYCHAIN AND PASSWORD_FILE)
    FILE(STRINGS ${PASSWORD_FILE} PASSWORD)
    EXECUTE_PROCESS(COMMAND /usr/bin/security unlock-keychain -p ${PASSWORD} ${KEYCHAIN} RESULT_VARIABLE RC)
    MESSAGE(STATUS "Unlocking keychain ${KEYCHAIN}, result code: ${RC}")
ENDIF()