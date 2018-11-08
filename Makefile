all: install

install:
	mkdir -p $(DESTDIR)/lib/udev/rules.d
	@cp -fr 60-eta-check-inputdevice.rules $(DESTDIR)/lib/udev/rules.d/60-eta-check-inputdevice.rules

	mkdir -p $(DESTDIR)/usr/bin
	@cp -fr eta-check-inputdevice $(DESTDIR)/usr/bin/eta-check-inputdevice

	mkdir -p $(DESTDIR)/lib/systemd/system
	@cp -fr eta-check-inputdevice.service $(DESTDIR)/lib/systemd/system/eta-check-inputdevice.service

uninstall:
	@rm -fr $(DESTDIR)/lib/udev/rules.d/60-eta-check-inputdevice.rules
	@rm -fr $(DESTDIR)/usr/bin/eta-check-inputdevice
	@rm -fr $(DESTDIR)/lib/systemd/system/eta-check-inputdevice.service

.PHONY: install uninstall

