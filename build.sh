#!/usr/bin/env bash
set -euo pipefail

PROJECT_NAME="TradingCardBrawl"
UPROJECT_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/${PROJECT_NAME}.uproject"

UE_ROOT_CANDIDATES=(
  "/Epic/UE_5.3"
  "$HOME/UnrealEngine"
  "/opt/UnrealEngine"
)

find_ue_root() {
  for path in "${UE_ROOT_CANDIDATES[@]}"; do
    if [[ -d "$path" ]]; then
      echo "$path"
      return 0
    fi
  done

  return 1
}

run_webgl_build() {
  local ue_root="$1"
  local uat_script=""

  if [[ -f "$ue_root/Engine/Build/BatchFiles/RunUAT.sh" ]]; then
    uat_script="$ue_root/Engine/Build/BatchFiles/RunUAT.sh"
  elif [[ -f "$ue_root/Engine/Build/BatchFiles/RunUAT.bat" ]]; then
    uat_script="$ue_root/Engine/Build/BatchFiles/RunUAT.bat"
  fi

  if [[ -z "$uat_script" ]]; then
    echo "Found Unreal Engine at '$ue_root' but RunUAT was not found."
    echo "Please verify your UE5.3 installation and try again."
    exit 1
  fi

  echo "Using Unreal Engine at: $ue_root"
  echo "Starting WebGL build for ${PROJECT_NAME}..."

  if [[ "$uat_script" == *.sh ]]; then
    "$uat_script" BuildCookRun \
      -project="$UPROJECT_PATH" \
      -platform=HTML5 \
      -clientconfig=Shipping \
      -build -cook -stage -pak -archive
  else
    "$uat_script" BuildCookRun \
      -project="$UPROJECT_PATH" \
      -platform=HTML5 \
      -clientconfig=Shipping \
      -build -cook -stage -pak -archive
  fi
}

main() {
  if ue_root="$(find_ue_root)"; then
    run_webgl_build "$ue_root"
  else
    echo "Unreal Engine 5.3 was not found in these locations:"
    for path in "${UE_ROOT_CANDIDATES[@]}"; do
      echo "  - $path"
    done
    echo "Download UE5.3 from: https://www.unrealengine.com/en-US/download"
    exit 1
  fi
}

main "$@"
