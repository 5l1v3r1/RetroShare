/*******************************************************************************
 * gui/common/NewFriendList.h                                                  *
 *                                                                             *
 * Copyright (C) 2011, Retroshare Team <retroshare.project@gmail.com>          *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU Affero General Public License as              *
 * published by the Free Software Foundation, either version 3 of the          *
 * License, or (at your option) any later version.                             *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU Affero General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Affero General Public License    *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                             *
 *******************************************************************************/

#pragma once

#include <set>

#include <QWidget>
#include <QTreeView>

#include "FriendListModel.h"
#include "retroshare/rsstatus.h"

namespace Ui {
    class NewFriendList;
}

class RSTreeWidgetItemCompareRole;
class QTreeWidgetItem;
class QToolButton;

class NewFriendList: public QWidget
{
	Q_OBJECT

	Q_PROPERTY(QColor textColorGroup READ textColorGroup WRITE setTextColorGroup)
	Q_PROPERTY(QColor textColorStatusOffline READ textColorStatusOffline WRITE setTextColorStatusOffline)
	Q_PROPERTY(QColor textColorStatusAway READ textColorStatusAway WRITE setTextColorStatusAway)
	Q_PROPERTY(QColor textColorStatusBusy READ textColorStatusBusy WRITE setTextColorStatusBusy)
	Q_PROPERTY(QColor textColorStatusOnline READ textColorStatusOnline WRITE setTextColorStatusOnline)
	Q_PROPERTY(QColor textColorStatusInactive READ textColorStatusInactive WRITE setTextColorStatusInactive)
public:
	enum Column
	{
		COLUMN_NAME         = 0,
		COLUMN_LAST_CONTACT = 1,
		COLUMN_IP           = 2,
		COLUMN_ID           = 3
	};

public:
	explicit NewFriendList(QWidget *parent = 0);
	~NewFriendList();

	// Add a tool button to the tool area
	void addToolButton(QToolButton *toolButton);
	void processSettings(bool load);
	void addGroupToExpand(const RsNodeGroupId &groupId);
	bool getExpandedGroups(std::set<RsNodeGroupId> &groups) const;
	void addPeerToExpand(const RsPgpId &gpgId);
	bool getExpandedPeers(std::set<RsPgpId> &peers) const;

	std::string getSelectedGroupId() const;
	void setColumnVisible(Column column, bool visible);
	void sortByColumn(Column column, Qt::SortOrder sortOrder);
	bool isSortByState();

	QColor textColorGroup() const { return mTextColorGroup; }
	QColor textColorStatusOffline() const { return mTextColorStatus[RS_STATUS_OFFLINE]; }
	QColor textColorStatusAway() const { return mTextColorStatus[RS_STATUS_AWAY]; }
	QColor textColorStatusBusy() const { return mTextColorStatus[RS_STATUS_BUSY]; }
	QColor textColorStatusOnline() const { return mTextColorStatus[RS_STATUS_ONLINE]; }
	QColor textColorStatusInactive() const { return mTextColorStatus[RS_STATUS_INACTIVE]; }

	void setTextColorGroup(QColor color) { mTextColorGroup = color; }
	void setTextColorStatusOffline(QColor color) { mTextColorStatus[RS_STATUS_OFFLINE] = color; }
	void setTextColorStatusAway(QColor color) { mTextColorStatus[RS_STATUS_AWAY] = color; }
	void setTextColorStatusBusy(QColor color) { mTextColorStatus[RS_STATUS_BUSY] = color; }
	void setTextColorStatusOnline(QColor color) { mTextColorStatus[RS_STATUS_ONLINE] = color; }
	void setTextColorStatusInactive(QColor color) { mTextColorStatus[RS_STATUS_INACTIVE] = color; }

public slots:
	void filterItems(const QString &text);
	void sortByState(bool sort);

	void setShowGroups(bool show);
	void setHideUnconnected(bool hidden);
	void setShowState(bool show);

private slots:

protected:
	void changeEvent(QEvent *e);
	void createDisplayMenu();

private:
	Ui::NewFriendList *ui;
	RsFriendListModel *mModel;
	QAction *mActionSortByState;

	QModelIndex getCurrentIndex() const;

	bool getCurrentNode(RsFriendListModel::RsNodeDetails& prof) const;
	bool getCurrentGroup(RsGroupInfo& prof) const;
	bool getCurrentProfile(RsFriendListModel::RsProfileDetails& prof) const;

	// Settings for peer list display
	bool mShowGroups;
	bool mShowState;
	bool mHideUnconnected;

	QString mFilterText;

	bool groupsHasChanged;
	std::set<RsNodeGroupId> openGroups;
	std::set<RsPgpId>   openPeers;

	/* Color definitions (for standard see qss.default) */
	QColor mTextColorGroup;
	QColor mTextColorStatus[RS_STATUS_COUNT];

	bool getOrCreateGroup(const std::string& name, uint flag, RsNodeGroupId& id);
	bool getGroupIdByName(const std::string& name, RsNodeGroupId& id);

	bool importExportFriendlistFileDialog(QString &fileName, bool import);
	bool exportFriendlist(QString &fileName);
	bool importFriendlist(QString &fileName, bool &errorPeers, bool &errorGroups);

private slots:
	void groupsChanged();
	void peerTreeWidgetCustomPopupMenu();
	void updateMenu();

	void pastePerson();

	void connectNode();
	void configureNode();
	void configureProfile();
	void chatNode();
	void copyFullCertificate();
	void addFriend();
	void msgNode();
	void msgGroup();
	void msgProfile();
	void recommendNode();
	void removeNode();
	void removeProfile();
	void createNewGroup() ;

	void addToGroup();
	void moveToGroup();
	void removeFromGroup();

	void editGroup();
	void removeGroup();

	void exportFriendlistClicked();
	void importFriendlistClicked();
};
