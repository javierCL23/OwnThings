#!/bin/bash

# Obtener lista de monitores activos
active_monitors=$(hyprctl monitors | grep "Monitor" | grep -v "disabled")

# Comprobar si HDMI-A-1 está activo
if echo "$active_monitors" | grep -q "HDMI-A-1"; then
    # HDMI está activo -> cambiar a modo portátil
    hyprctl keyword monitor "eDP-1,1920x1080@60,0x0,1"
    hyprctl keyword monitor "HDMI-A-1,disable"
else
    # HDMI no está activo -> cambiar a modo HDMI
    hyprctl keyword monitor "HDMI-A-1,2560x1440@143.91,0x0,1"
    hyprctl keyword monitor "eDP-1,disable"
fi
