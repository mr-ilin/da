#!/usr/bin/env bash

set -o errexit
set -o pipefail
set -o nounset

function main() {
  # Компилируем.
  if ! make benchmark ; then
    echo "ERROR: Failed to compile file."
    exit 1
  fi

  local test_dir=tests
  rm -rf ${test_dir}
  mkdir -p ${test_dir}

  # Генерируем тесты.
  if ! python3 test_generator.py ${test_dir} "$1" "$2" ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
  fi

  # Запускаем тесты и сравниваем ответ.
  for test_file in $(ls ${test_dir}/*.t); do
    echo "Execute ${test_file}"

    local exe_file=benchmark
    if ! ./${exe_file} < ${test_file}; then
      echo "ERROR"
      continue
    fi
  done
  rm -rf ${test_dir}
}

main $@
