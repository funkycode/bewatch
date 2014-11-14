import bb.cascades 1.0

TabbedPane {
    showTabsOnActionBar: true
    Tab {
        title: qsTr("Tab") + Retranslate.onLocaleOrLanguageChanged
        Page {
            Container{
                layout: DockLayout {
                    
                }

            ListView {
                dataModel: watchlist.return_w_list();
                id: dtm
                function connect(address)
                {
                    watchlist.connect(address);
                    
                }
                function connect_spp(address)
                {
                    watchlist.connect_spp(address);
                
                }
                function refresh()
                {
                    dtm.dataModel = null
                    
                    watchlist.update_w_list();
                    dtm.dataModel = watchlist.return_w_list();
                }
                listItemComponents: [
                    ListItemComponent {
                        type: "header"
                        
                        Header {
                            title: ListItemData
                        }
                    },
                    
                    ListItemComponent {
                        type: "item"
                        id: listItem
                        
                        Container {
                            id : itemContainer
                            Label {
                                text: "Name: " + ListItemData.watchName 
                            }
                            
                            	
                            Label{
                                text:  "Mac: " +ListItemData.watchAddress
                            
                            }
                            
                            Label{
                                text:  "Type: " +ListItemData.watchType
                            
                            }
                            Label{
                                text:  "Class: " +ListItemData.watchClass
                            
                            }
                            
                            Button {
                                id: conn
                                horizontalAlignment: HorizontalAlignment.Center
                                verticalAlignment: verticalAlignment.Bottom
                                text: "connect"
                                onClicked: {
                                    itemContainer.ListItem.view.connect(ListItemData.watchAddress);
                                 
                                   
                                }
                            }
                            Button {
                                id: conn2
                                horizontalAlignment: HorizontalAlignment.Center
                                verticalAlignment: verticalAlignment.Bottom
                                text: "connect2"
                                onClicked: {
                                    itemContainer.ListItem.view.connect_spp(ListItemData.watchAddress);
                                
                                
                                }
                            }
                           
                            contextActions: ActionSet {
                                ActionItem {
                                    id: testaction
                                    title: "connect"
                                    onTriggered: {
                                        itemContainer.ListItem.view.connect(ListItemData.watchAddress);
                                    }
                                    
                                }
                                ActionItem {
                                        id: testaction2
                                        title: "connect 2"
                                        onTriggered: {
                                            itemContainer.ListItem.view.connect_spp(ListItemData.watchAddress);
                                        }
                                    
                                    }
                                ActionItem {
                                    id: testaction3
                                    title: "refresh all"
                                    onTriggered: {
                                        
                                        itemContainer.ListItem.view.refresh();
                       
                                       
                                        
                                    }
                                
                                }
                            }
                        
                        
                       }
                    }
                ]
            }
        
       
    }
         
        }
    } 
}
