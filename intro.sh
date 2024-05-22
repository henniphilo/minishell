#!/bin/sh
# intro.sh - Display a fancy visual intro with large ASCII art and emojis in pink color

# ANSI color code for pink (light magenta)
PINK='\033[1;32m'
NC='\033[0m' # No Color

# Generate large ASCII art using figlet
ASCII_ART=$(figlet -f wideterm.tlf "Welcome to our Minishell")

# Intro message with ASCII art and emojis
echo "${PINK}"
echo "🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺"
echo "🌺🌺🌺$ASCII_ART🌺🌺🌺"
echo "🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺🌺"
echo "${NC}"
