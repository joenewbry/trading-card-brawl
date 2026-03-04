#!/bin/bash

UE_PATH="/Users/Shared/Epic Games/UE_5.7"
PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_FILE="$PROJECT_DIR/TradingCardBrawl.uproject"
UBT="$UE_PATH/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool"
EDITOR="$UE_PATH/Engine/Binaries/Mac/UnrealEditor"

echo "=============================="
echo " Trading Card Brawl Builder"
echo "=============================="
echo "Engine: $UE_PATH"
echo "Project: $PROJECT_FILE"
echo ""

if [ ! -d "$UE_PATH" ]; then
  echo "ERROR: UE5.7 not found at $UE_PATH"
  echo "Download from: https://www.unrealengine.com/en-US/download"
  exit 1
fi

ACTION="${1:-open}"

case "$ACTION" in
  open)
    echo "Opening project in UE5.7 editor..."
    open "$PROJECT_FILE"
    ;;
  build)
    echo "Building TradingCardBrawl (Mac, Development)..."
    "$UBT" TradingCardBrawl Mac Development -Project="$PROJECT_FILE" -WaitMutex
    ;;
  cook)
    echo "Cooking content..."
    "$EDITOR" "$PROJECT_FILE" -run=Cook -TargetPlatform=HTML5 -Unversioned -fileopenlog
    ;;
  regen)
    echo "Regenerating Xcode project files..."
    "$UE_PATH/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh" -project="$PROJECT_FILE" -game -mac
    ;;
  *)
    echo "Usage: ./build.sh [open|build|cook|regen]"
    echo "  open  — Open project in UE5.7 editor (default)"
    echo "  build — Compile C++ source"
    echo "  cook  — Cook content for HTML5/WebGL"
    echo "  regen — Regenerate Xcode project files"
    ;;
esac
