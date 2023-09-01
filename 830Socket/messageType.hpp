#pragma once
enum MyEnum
{
	MSG_SHOW,
	MSG_JOIN,
	MSG_CREATE,
	MSG_TALK,
};

class msgHead {

public:
	int msgType;  // 消息类型
	int dataLen;  // 消息长度
};

// join,create,talk,leave

class msgShow : public msgHead {
public:
	msgShow() {
		msgType = MSG_SHOW;
		dataLen = sizeof(msgShow);
	}

};

class msgJoin : public msgHead {
public:
	int roomId;
	msgJoin(int Id) {
		msgType = MSG_JOIN;
		dataLen = sizeof(msgJoin);
		roomId = Id;
	}
};


class msgCreate : public msgHead {
public:
	msgCreate() {
		msgType = MSG_CREATE;
		dataLen = sizeof(msgCreate);
	}
};

class msgTalk : public msgHead {
public:
	msgTalk() {
		msgType = MSG_TALK;
		dataLen = sizeof(msgTalk);
	}
};





