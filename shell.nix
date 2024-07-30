{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gnumake
    pkgs.gcc
    pkgs.pkg-config
    pkgs.xorg.libX11
    pkgs.xorg.libXft
    pkgs.xorg.libXinerama
    pkgs.xorg.libXext
    pkgs.fontconfig
    pkgs.freetype
  ];
}
