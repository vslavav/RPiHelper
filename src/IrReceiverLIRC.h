/*
 * IrReceiverLIRC.h
 *
 *  Created on: 2019-02-26
 *      Author: pi
 */

#ifndef IRRECEIVERLIRC_H_
#define IRRECEIVERLIRC_H_

class IrReceiverLIRC {
	bool _IsStopCommanded;
public:
	IrReceiverLIRC();
	virtual ~IrReceiverLIRC();
	void Init();
	void Init_IO();
	void Run();
	void Start();
	void Stop();
};

#endif /* IRRECEIVERLIRC_H_ */
