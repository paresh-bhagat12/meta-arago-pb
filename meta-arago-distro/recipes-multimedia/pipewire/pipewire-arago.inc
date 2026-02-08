PR:append = ".arago1"

# Pipewire service for all platforms
FILESEXTRAPATHS:prepend := "${THISDIR}/pipewire:"
SRC_URI:append = " file://pipewire.service"

# AM62D-specific config files
FILESEXTRAPATHS:prepend:am62dxx-evm := "${THISDIR}/pipewire:"
SRC_URI:append:am62dxx-evm = " \
    file://90-pipewire-sink.conf \
    file://91-pipewire-source.conf \
"

do_install:append() {
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${UNPACKDIR}/pipewire.service ${D}${systemd_system_unitdir}/
}

do_install:append:am62dxx-evm() {
    install -d ${D}${sysconfdir}/pipewire/pipewire.conf.d
    install -m 0644 ${UNPACKDIR}/90-pipewire-sink.conf ${D}${sysconfdir}/pipewire/pipewire.conf.d/
    install -m 0644 ${UNPACKDIR}/91-pipewire-source.conf ${D}${sysconfdir}/pipewire/pipewire.conf.d/
}

FILES:${PN} += " ${sysconfdir}"

PACKAGECONFIG:append = " pipewire-jack"
PACKAGECONFIG:remove = "jack"
