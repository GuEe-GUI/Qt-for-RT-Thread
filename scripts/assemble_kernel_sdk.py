#!/usr/bin/env python3
"""Assemble a relocatable RT-Thread kernel-mode Qt SDK."""

import argparse
import shutil
import sys
from pathlib import Path
from typing import Optional


SDK_DIRECTORIES = ("include", "lib", "plugins", "qml")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Assemble the Qt installation consumed by integrations/kernel/SConscript."
    )
    parser.add_argument("qt_install_prefix", type=Path)
    parser.add_argument("output_sdk", type=Path)
    parser.add_argument(
        "demo_archive",
        nargs="?",
        type=Path,
        help="optional static Qt demo application archive",
    )
    return parser.parse_args()


def copy_directory(source: Path, destination: Path) -> None:
    if not source.is_dir():
        raise FileNotFoundError(f"missing Qt install directory: {source}")
    shutil.copytree(source, destination, copy_function=shutil.copy2)


def assemble(qt_prefix: Path, output: Path, demo: Optional[Path]) -> None:
    qt_prefix = qt_prefix.expanduser().resolve()
    output = output.expanduser().resolve()

    if output.exists():
        raise FileExistsError(f"output already exists; use a new directory: {output}")

    missing = [name for name in SDK_DIRECTORIES if not (qt_prefix / name).is_dir()]
    if missing:
        raise FileNotFoundError(
            f"incomplete Qt installation at {qt_prefix}; missing: {', '.join(missing)}"
        )

    # Validate every input before creating the destination so a bad invocation
    # never leaves a partial SDK behind.
    if demo is not None:
        demo = demo.expanduser().resolve()
        if not demo.is_file():
            raise FileNotFoundError(f"Qt demo archive not found: {demo}")

    try:
        output.mkdir(parents=True)
        for name in SDK_DIRECTORIES:
            copy_directory(qt_prefix / name, output / name)

        if demo is not None:
            examples = output / "examples"
            examples.mkdir()
            shutil.copy2(demo, examples / demo.name)
    except Exception:
        # The output did not exist before this invocation, so removing only
        # this exact directory is safe and prevents a corrupt SDK from being used.
        if output.exists():
            shutil.rmtree(output)
        raise


def main() -> int:
    args = parse_args()
    try:
        assemble(args.qt_install_prefix, args.output_sdk, args.demo_archive)
    except (OSError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1

    print(f"assembled RT-Thread kernel Qt SDK: {args.output_sdk.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
