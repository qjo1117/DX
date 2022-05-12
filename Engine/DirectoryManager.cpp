#include "pch.h"
#include "DirectoryManager.h"

void DirectoryManager::Init()
{
	m_path = fs::current_path().remove_filename();


	CreateFileInfos();

	/* ------ Test ------ */
	vector<Ref<FileInfo>> vecFileInfos;
	FindFileInfo(m_pFileInfo, vecFileInfos, ".h");
}

void DirectoryManager::Update()
{

	// 갱신
	//if (m_time != fs::last_write_time(m_path)) {
	//	m_time = fs::last_write_time(m_path);
	//	CreateFileInfos();
	//}
	//if (CheckUpdateFileInfo(m_pFileInfo)) {
	//	CreateFileInfos();
	//}

}

void DirectoryManager::End()
{
	ClearFileInfos(m_pFileInfo);
}

void DirectoryManager::AddFileInfo(fs::path p_pathInfo, const string& p_strPath)
{
	vector<string> vecPath = Utils::Split(p_strPath, '\\');

	if (p_pathInfo.extension().empty() == true) {
		// TODO : 폴더
		Ref<FileInfo> fileInfo = FindFileInfo(m_pFileInfo, vecPath);
		if (fileInfo == nullptr) {
			fileInfo = make_shared<FileInfo>();
			fileInfo->PathInfo = p_pathInfo;
			fileInfo->Parent = nullptr;
			fileInfo->Name = vecPath[vecPath.size() - 1];
			fileInfo->Type = FILE_TYPE::FOLDER;
			fileInfo->Time = fs::last_write_time(p_pathInfo);
			m_pFileInfo = fileInfo;
		}
		else {
			Ref<FileInfo> tempInfo = make_shared<FileInfo>();
			tempInfo->PathInfo = p_pathInfo;
			tempInfo->Parent = fileInfo;
			tempInfo->Name = vecPath[vecPath.size() - 1];
			tempInfo->Type = FILE_TYPE::FOLDER;
			tempInfo->Time = fs::last_write_time(p_pathInfo);
			fileInfo->File.push_back(tempInfo);
		}
	}
	else {
		// TODO : 파일
		Ref<FileInfo> fileInfo = FindFileInfo(m_pFileInfo, vecPath);
		Ref<FileInfo> tempInfo = make_shared<FileInfo>();
		tempInfo->PathInfo = p_pathInfo;
		tempInfo->Parent = fileInfo;
		tempInfo->Name = vecPath[vecPath.size() - 1];
		tempInfo->Type = FILE_TYPE::FILE;
		tempInfo->Time = fs::last_write_time(p_pathInfo);
		fileInfo->File.push_back(tempInfo);
	}
}

Ref<FileInfo> DirectoryManager::FindFileInfo(Ref<FileInfo> p_info, const vector<string>& p_fileName, int32 index)
{
	if (p_fileName.size() - 1 == index) {
		return p_info;
	}

	for (Ref<FileInfo>& info : p_info->File) {
		if (info->Name == p_fileName[index]) {
			return FindFileInfo(info, p_fileName, ++index);
		}
	}
	return nullptr;
}

void DirectoryManager::CreateFileInfos()
{
	ClearFileInfos(m_pFileInfo);

	fs::path rootPath = fs::current_path().remove_filename();
	AddFileInfo(rootPath, "DX");
	for (auto& entry : fs::recursive_directory_iterator(rootPath)) {
		string strPath = entry.path().string();
		strPath = strPath.substr(rootPath.string().length(), strPath.size());
		AddFileInfo(entry.path(), strPath);
	}

}

void DirectoryManager::ClearFileInfos(Ref<FileInfo> p_info)
{
	if (p_info == nullptr) {
		return;
	}

	for (auto& info : p_info->File) {
		ClearFileInfos(info);
		if (info->Parent) {
			info->Parent = nullptr;
		}
		info = nullptr;

	}
	p_info->File.clear();
}

void DirectoryManager::CheckUpdateFileInfo(Ref<FileInfo> p_info)
{
	//if (p_info->Time != fs::last_write_time(p_info->PathInfo)) {
	//	return ;
	//}
	for (auto& info : p_info->File) {
		CheckUpdateFileInfo(info);
	}
	return;
}

void DirectoryManager::FindFileInfo(Ref<FileInfo> root, vector<Ref<FileInfo>>& p_vecFileInfo, const string& extension)
{
	if (root == nullptr) {
		return;
	}

	for (Ref<FileInfo>& info : root->File) {
		if (info->PathInfo.extension().string() == extension) {
			p_vecFileInfo.push_back(info);
		}
		FindFileInfo(info, p_vecFileInfo, extension);
	}
}
