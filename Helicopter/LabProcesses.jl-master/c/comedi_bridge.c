#include <stdio.h>      /* for printf() */
#include <comedilib.h>

int range = 0;
int aref = AREF_GROUND;
comedi_t *it;

int comedi_write(int comediNbr, int subdev, int chan, int writeValue) {
	static int retval;
	retval = comedi_data_write(it, subdev, chan, range, aref, writeValue);
    return retval;
}

int comedi_read(int comediNbr, int subdev, int chan) {
	lsampl_t data;
	comedi_data_read(it, subdev, chan, range, aref, &data);
    return data;
}

int comedi_start(int comediNbr) {
	it = comedi_open("/dev/comedi0");
		if(it == NULL)
	{
		comedi_perror("comedi_open_error");
		return -1;
	}
	return 0;
}

void comedi_stop(int comediNbr) {
	// Ad-hoc. Should be updated:
	comedi_data_write(it, 1, 0, range, aref, 32767);
	comedi_data_write(it, 1, 1, range, aref, 32767);
	comedi_close(it);
}



