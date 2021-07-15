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
  local work_dir="/Users/mr-ilin/Documents/Labs/da/cp_da"
  local bin="solution"  # исполняемый файл
  local makefile_target="all"

  local unit_test_exe="unit_test"
  local test_gen_program="${work_dir}/test/test_generator.py" # скрипт для тестов
  local tests_cnt=10
  local test_len=100

  declare -a failed_tests

  local test_dir="${work_dir}/test/test_files"

  # чтобы с cmake работало???
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

  rm -f ${test_dir}/*.t
  # Генерируем тесты.
  log_info "Generating tests..."
  if ! python3 ${test_gen_program} ${test_dir} "$1" "$2" ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
  fi

  # Проверяем тесты
  last_encoding="last_encoding.txt"
  last_decoding="last_decoding.txt"

  for test_file in $(ls ${test_dir}/*.t); do
#    log_info "Encoding ${test_file}..."

    # compressing
    local to_compress="$(<${test_file})"
    local input="compress
    ${to_compress}"

    if ! ./${bin} < <(echo "${input}") >${last_encoding}; then
      log_error "ERROR"
      failed_tests+=( "${test_file}" )
      continue
    fi

#    log_info "Decoding ${test_file}..."

    # decompressing
    local to_decompress="$(<${last_encoding})"
    input="decompress
    ${to_decompress}"

    if ! ./${bin} < <(echo "${input}") >${last_decoding}; then
      log_error "ERROR"
      failed_tests+=( "${test_file}" )
      continue
    fi

    if ! diff -u ${test_file} ${last_decoding} ; then
        echo "Failed"
        failed_tests+=( "${test_file}" )
#    else
#        echo "OK"
    fi
  done


  if [ ${#failed_tests[@]} -eq 0 ]; then
    log_info "No failed tests, hooray"
  else
    log_info "Failed tests:"
    for test in ${failed_tests[@]}; do
      echo ${test}
      cat ${test}
    done
  fi
}

main $@
