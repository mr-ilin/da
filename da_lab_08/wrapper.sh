#! /usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail

function _log()
{
  local type=$1
  local message=$2
  local date=$(date +"%Y-%m-%d %H:%M:%S")
  echo "[${date}] [${type}] ${message}"
}

function log_info()
{
  local message=$1
  _log "INFO" "${message}"
}

function log_error()
{
  local message=$1
  _log "ERROR" "${message}"
}

function main()
{
  local bin="solution"
  local makefile_target="all"
  local unit_test_exe="unit_test"

  declare -a failed_tests

  local test_dir="tests"

  # Компилируем
  log_info "Compiling..."
  if ! make ${makefile_target}; then
    log_error "ERROR: Failed to compile file."
    exit 1
  fi

  # Проверяем юнит тесты
  log_info "Making unittest..."
  if ! make test ; then
    log_error "ERROR: Failed to make unittest."
    return 1
  fi
  if ! ./${unit_test_exe} ; then
    log_error "ERROR: Failed while running unittest."
  fi

  # Проверяем ручные тесты
  last_answer="answer_file"
  for test_file in $(ls ${test_dir}/*.t); do
    log_info "Executing ${test_file}..."

    if ! ./${bin} < ${test_file} >${last_answer}; then
      log_error "ERROR"
      failed_tests+=( "${test_file}" )
      continue
    fi

    local answer_file="${test_file%.*}"
    if ! diff -u "${answer_file}.a" ${last_answer} ; then
        echo "Failed"
        failed_tests+=( "${test_file}" )
    else
        echo "OK"
    fi
  done


  if [ ${#failed_tests[@]} -eq 0 ]; then
    log_info "No failed tests, hooray"
  else
    log_info "Failed test:"
    for test in ${failed_tests[@]}; do
      echo ${test}
    done
  fi
}

main $@
