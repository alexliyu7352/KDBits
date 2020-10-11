// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// KDBits.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


entry bdecode(const path &file) //����Ϊ�����ļ�·��
{
	std::locale prev_loc = std::locale::global(std::locale(""));
	ifstream fs(file, ifstream::binary);	//�����Ʒ�ʽ�������ļ�
	std::locale::global(prev_loc);
	if(fs.is_open()) //�򿪳ɹ�
	{
		fs.unsetf(ifstream::skipws);//�����ո�
		return libtorrent::bdecode(std::istream_iterator<char>(fs), std::istream_iterator<char>());//���������ļ�
	}
	else
		return entry();
}

bool bencode(const path &file, const entry &e) //����Ϊ�����ļ�·��
{
	std::locale prev_loc = std::locale::global(std::locale(""));
	ofstream fs(file, ofstream::binary);	//�����Ʒ�ʽ�������ļ�
	std::locale::global(prev_loc);
	if(!fs.is_open()) //��ʧ�ܾ��˳�
		return false;

	libtorrent::bencode(std::ostream_iterator<char>(fs), e);//����д���ļ�
	return true;
}

wstring LoadStringW(UINT id) 
{
	wchar_t buf[1024]; //������ΪUNICODE���룬�������溯������ʵ������LoadStringW�ĵ���
	int len = LoadString(GetModuleHandle(NULL), id, buf, 1024);
	return wstring(buf, len);
}

string LoadStringA(UINT id)
{
	char buf[1024];
	int len = LoadStringA(GetModuleHandle(NULL), id, buf, 1024);
	return string(buf, len);
}

wstring mbstowcs(const string &str) 
{
	std::locale prev_loc = std::locale::global(std::locale(""));
	size_t len = mbstowcs(NULL, str.c_str(), str.length());	//����ת����Ŀ��ַ����ַ�����
	std::locale::global(prev_loc);
	boost::scoped_array<wchar_t> buf(new wchar_t[len+1]);
	prev_loc = std::locale::global(std::locale(""));
	len = mbstowcs(buf.get(), str.c_str(), str.length());
	std::locale::global(prev_loc);
	if(len == static_cast<size_t>(-1)) 
		throw runtime_error("mbstowcs(): invalid multi-byte character");

	return wstring(buf.get(), len);
}

string wcstombs(const wstring &str) 
{
	std::locale prev_loc = std::locale::global(std::locale(""));
	size_t len = wcstombs(NULL, str.c_str(), 0);
	std::locale::global(prev_loc);
	boost::scoped_array<char> buf(new char[len+1]);
	prev_loc = std::locale::global(std::locale(""));
	len = wcstombs(buf.get(), str.c_str(), len);
	std::locale::global(prev_loc);
	if(len == static_cast<size_t>(-1)) 
		throw runtime_error("wcstombs(): unable to convert character");

	return string(buf.get(), len);
}

bool safe_create_directories(const path& ph)
{
	if (ph.empty() || exists(ph))
	{
		if (!ph.empty() && !is_directory(ph))
			boost::throw_exception(boost::filesystem::filesystem_error());
		return false;
	}
	// First create branch, by calling ourself recursively
	safe_create_directories(ph.branch_path());
	// Now that parent's path exists, create the directory
	boost::filesystem::create_directory(ph);
	return true;
}

path GetTorrentPath()
{
	char folder[MAX_PATH];
	GetModuleFileNameA(NULL, folder, sizeof(folder));
	path p(folder);
	p = p.branch_path();
	p/="KeydoneBT/Torrent";

	if(!boost::filesystem::exists(p))
		safe_create_directories(p);

	return p;
}

path GetFastResumePath()
{
	char folder[MAX_PATH];
	GetModuleFileNameA(NULL, folder, sizeof(folder));
	path p(folder);
	p = p.branch_path();
	p/="KeydoneBT/FastResume";

	if(!boost::filesystem::exists(p))
		safe_create_directories(p);

	return p;
}

path GetModulePath()
{
	char folder[MAX_PATH];
	GetModuleFileNameA(NULL, folder, sizeof(folder));
	path p(folder);
	p = p.branch_path();

	if(!boost::filesystem::exists(p))
		safe_create_directories(p);

	return p;
}

//�����ݸ�ʽ��Ϊ�ı��ַ�
wchar_t * formatData(double s)
{
	double         downloaded;
	const wchar_t *units;
	if(s >= 1073741824) 
	{
		downloaded = s / 1073741824.0;
		units      = L"GB";
	}
	else if(s >= 1048576) 
	{
		downloaded = s / 1048576.0;
		units      = L"MB";
	}
	else if(s >= 1024) 
	{
		downloaded = s / 1024.0;
		units      = L"KB";
	}
	else 
	{
		downloaded = s;
		units      = L"B";
	}
	static wchar_t buf[64];
	swprintf(buf , L"%.2f %s", downloaded, units);
	return buf;
}
