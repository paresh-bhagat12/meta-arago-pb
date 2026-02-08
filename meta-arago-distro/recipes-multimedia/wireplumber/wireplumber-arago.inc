PR:append = ".arago1"

FILESEXTRAPATHS:prepend:am62dxx-evm := "${THISDIR}/wireplumber:"

SRC_URI:append:am62dxx-evm = " \
    file://set-audio-defaults.sh \
    file://set-audio-defaults.service \
"

inherit systemd

# Enable wireplumber for all platforms
SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE:${PN} = "wireplumber.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"

do_install:append:am62dxx-evm() {
    # Install the script
    install -d ${D}${bindir}
    install -m 0755 ${UNPACKDIR}/set-audio-defaults.sh ${D}${bindir}/

    # Install the systemd service file
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${UNPACKDIR}/set-audio-defaults.service ${D}${systemd_system_unitdir}/
}

SYSTEMD_PACKAGES:am62dxx-evm = "${PN}"
SYSTEMD_SERVICE:${PN}:am62dxx-evm = "wireplumber.service set-audio-defaults.service"
SYSTEMD_AUTO_ENABLE:${PN}:am62dxx-evm = "enable"

FILES:${PN} += " \
    ${bindir} \
"
