{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gnumake
    gcc
    pkg-config
    xorg.libX11
    xorg.libXft
    xorg.libXinerama
    xorg.libXext
    fontconfig
    freetype
    imlib2
    libexif
  ];
}
