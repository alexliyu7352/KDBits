#pragma once

enum DOWN_SETUP
{
	down_now  = 0,
	down_late = 1
};

struct PreDownloadProperty
{
	friend class boost::serialization::access;
	operator path() const { return SavePath; } //�����Ǹ�С����,��Ϊ�Ҳ�֪����ô����(struct::struct::member)��Աָ��
	path        SavePath;			 // ���·��
	int         UploadLimit;		 // ����ϴ��ٶ�
	int         DownloadLimit;		 // ��������ٶ�
	DOWN_SETUP  RunSetup;			 // �������ػ����Ժ�����
	bool        bPreAlloc;			 // ����ǰ�Ƿ�Ԥ������̿ռ�
	bool        bReCheckDataCalcSum; // �ϵ�����ʱ�Ƿ����¼���Ѿ����ص����ݵ�������
	int         MaxTaskNum;			 // ͬʱ���ص����������
	UPDATE_RULE UpdateRule;			 // �ֶ����»����Զ�����
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		ar & UploadLimit;
		ar & DownloadLimit;
		ar & RunSetup;
		ar & bPreAlloc;
		ar & bReCheckDataCalcSum;
		ar & MaxTaskNum;
		ar & UpdateRule;
		if (typename Archive::is_loading())
		{
			string strTemp;
			ar & strTemp;
			SavePath = strTemp;
		}
		else if (typename Archive::is_saving())
		{
			string strTemp = SavePath.string();
			ar & strTemp;
		}
	}
};

struct DownloadNode
{
	friend class boost::serialization::access;
	string              Name;								// ����
	string              FileName;							// �����ļ����ļ���
	torrent_handle      Handle;								// �������������ľ��
	PreDownloadProperty DownNodeProperty;					// ���ز���
	wstring             cols[DOWNLOADLIST_COLUMN_NUMBER];	// ��ʾ�ַ��������󶨵��б�ؼ��ϣ�ÿ�а�һ��Ԫ�أ�
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		ar & FileName;
		ar & DownNodeProperty;
	}
};

extern void AsynWaitHandler(boost::function<void (void)> ParseHandler,  path TorrentFile);

class CDownloadList
{
	friend class boost::serialization::access;
public:
	CDownloadList(void);
public:
	~CDownloadList(void);
public:
	typedef vector<DownloadNode>::const_iterator node_iterator;
protected:
	session m_Session;
protected:
	vector<DownloadNode> m_List;
protected:
	bool Load(void);
	bool Save(void);
public:
	bool SetTransferSpeed(int iUploadSpeed, int iDownloadSpeed);
public:
	bool BindPort(int iFristPort, int iLastPort);
public:
	void Initialize(void);
public:
	void Exit(void);
public:
	void ParseTorrentFile(path TorrentFile, torrent_info * TorrentInfo);
public:
	void AddTask(path TorrentFile, PreDownloadProperty & PreDownProperty, boost::function<bool (torrent_info &, PreDownloadProperty &)> ShowPreDownloadDialog, boost::function<void (boost::function<void (void)>, path)> AsynWaitHandler);
public:
	bool DeleteTask(string Name);
public:
	void UpdateState(void);
public:
	void SetDownloadProperty(PreDownloadProperty & DownloadProperty);
public:
	const size_t Count(void);
public:
	const DownloadNode & operator[](const size_t index);
public:
	node_iterator begin(void);
	node_iterator end(void);
protected:
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		if (typename Archive::is_loading())
		{
			vector<DownloadNode> List;
			ar & List;
			std::for_each(
				List.begin(),
				List.end(),
				bind(&CDownloadList::AddTask, this, bind(&DownloadNode::FileName, _1), bind<PreDownloadProperty &>(&DownloadNode::DownNodeProperty, _1), boost::function<bool (torrent_info &, PreDownloadProperty &)>(), &AsynWaitHandler)
				);
		}
		else if (typename Archive::is_saving())
		{
			ar & m_List;
		}
	}
};

BOOST_CLASS_VERSION(CDownloadList, 1)
BOOST_CLASS_TRACKING(CDownloadList, boost::serialization::track_never)

extern CDownloadList g_DownloadList;
