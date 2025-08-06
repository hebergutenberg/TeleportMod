autoptr ref TStringArray g_activatedTeleportMods = {};
static ref TStringArray GetActivatedTeleportMods()
{
    if (!g_activatedTeleportMods) g_activatedTeleportMods = {};
    return g_activatedTeleportMods;
}

static int SearchActivatedTeleportMod(string teleportName) {
    foreach (auto key, auto name: g_activatedTeleportMods)
    {
        if (name == teleportName) {
            return key;
        }
    }
    return -1;
}

static void InsertActivatedTeleportMod(string teleportName) {
    if (SearchActivatedTeleportMod(teleportName) < 0) {
        g_activatedTeleportMods.Insert(teleportName);
    }
}

static void RemoveActivatedTeleportMod(string teleportName) {
    int index = SearchActivatedTeleportMod(teleportName);
    if (index >= 0) {
        g_activatedTeleportMods.Remove(index);
    }
}

class TeleportModPlayerCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(3);
    }
};

class TeleportModPlayer: ActionContinuousBase
{
    protected ref LO_TeleportConfig m_TeleportConfig;  // Reference to teleport configuration object

    void TeleportModPlayer()
    {
        m_CallbackClass = TeleportModPlayerCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET; //CMD_ACTIONFB_INTERACT;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_FullBody = true;
        m_Text = "#STR_Controls_Interact";
        LoadTeleportConfig();  // Load teleport configuration
    }

    protected void LoadTeleportConfig()
    {
        m_TeleportConfig = JsonConfigManager.LoadTeleportConfig();  // Load configuration using JsonConfigManager
    }

    override void CreateConditionComponents()
    {
        m_ConditionTarget = new CCTBase; //CCTCursorParent(UAMaxDistances.DEFAULT);
        m_ConditionItem = new CCINone;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return true;
    }
    
    override void OnStartServer(ActionData action_data ) {}

    override void OnFinishProgressServer(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        ActionTarget target = action_data.m_Target;
        Object targetObject = target.GetObject();
        LO_TeleportEntry entry = GetTeleportEntry(targetObject);

        // Teleportation logic
        if (entry) {
            bool canTeleport = false;
            ItemBase heldItem = null;
            
            if (entry.EnableTeleport) {
                if ("TeleportModPoint" == targetObject.GetType() && vector.Distance(targetObject.GetPosition(), player.GetPosition()) <= entry.CheckRadius)
                {
                    if (SearchActivatedTeleportMod(entry.TeleportName) < 0) {
                        if (entry.RequiredItem != "") {
                            heldItem = player.GetItemInHands();
                            if (heldItem && heldItem.GetType() == entry.RequiredItem)
                            {
                                int healthLevel = heldItem.GetHealthLevel();
                                if (healthLevel < GameConstants.STATE_RUINED) {
                                    // Apply damage if configured
                                    if (entry.RequiredItemDamagePercent > 0) {
                                        int currentHealth = heldItem.GetHealth();
                                        int maxHealth = heldItem.GetMaxHealth();
                                        heldItem.SetHealth(currentHealth - Math.Floor(maxHealth / 100 * entry.RequiredItemDamagePercent));
                                    }
                                    
                                    canTeleport = true;
                                    
                                    if (entry.TeleportActiveTimeSeconds > 0) {
                                        InsertActivatedTeleportMod(entry.TeleportName);
                                        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RemoveActivatedTeleportMod, entry.TeleportActiveTimeSeconds * 1000, false, entry.TeleportName);    
                                    }
                                }
                            }
                        } else {
                            canTeleport = true;
                        }
                    } else {
                        canTeleport = true;
                    }
                }

                if (canTeleport) {
                    // Consume/destroy the required item if configured
                    if (entry.ConsumeRequiredItem && heldItem && entry.RequiredItem != "") {
                        // Remove item from player's hands and destroy it
                        GetGame().ObjectDelete(heldItem);
                        Print("Consumed required item: " + entry.RequiredItem);
                    }
                    
                    // Play teleport sound if enabled
                    if (entry.EnableTeleportSound && entry.TeleportSoundFile != "") {
                        PlayTeleportSound(player.GetPosition(), entry.TeleportSoundFile, entry.TeleportSoundRadius, entry.TeleportSoundVolume);
                    }
                    
                    player.SetPosition(entry.TeleportPosition);  // Teleportation
                    
                    // Play sound at destination if enabled
                    if (entry.EnableTeleportSound && entry.TeleportSoundFile != "") {
                        PlayTeleportSound(entry.TeleportPosition, entry.TeleportSoundFile, entry.TeleportSoundRadius, entry.TeleportSoundVolume);
                    }
                } else {
                    // Notification about missing item
                    player.MessageStatus(entry.MissingItemMessage);
                }
            }
        }
    }

    void PlayTeleportSound(vector position, string soundFile, float radius, float volume)
    {
        // Method that works in DayZ 1.28 - using SEffectManager
        EffectSound effect = SEffectManager.PlaySound(soundFile, position);
        
        if (effect) {
            Print("Playing teleport sound: " + soundFile + " at position " + position.ToString());
        } else {
            Print("Failed to play teleport sound: " + soundFile);
        }
    }

    LO_TeleportEntry GetTeleportEntry(Object targetObject) {
        foreach (ref LO_TeleportEntry entry : m_TeleportConfig.TeleportEntries)
        {
            if (vector.Distance(targetObject.GetPosition(), entry.ObjectCoordinates) < 3) {
                return entry;
            }
        }
        return null;
    }
    
    override typename GetInputType()
    {
        return ContinuousInteractActionInput;
    }

    override bool HasProgress()
    {
        return true;
    }
    
    override bool HasTarget()
    {
        return true;
    }
    
    override bool CanBeUsedInVehicle()
    {
        return false;
    }
};

modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
        
        // Register new action
        actions.Insert(TeleportModPlayer);
    }
};

class TeleportModPoint extends ItemBase
{
    void TeleportModPoint()
    {
        SetSynchDirty();
        SetLifetime(600); // Object lifetime if needed
    }
    
    override void SetActions()
    {
        super.SetActions();        
        AddAction(TeleportModPlayer);
    }

    string Get_StaticReturnItem()
    {
        return "TeleportModPoint";
    }
    
    override bool IsHealthVisible()
    {
        return false;
    }
    
    override bool IsBuilding()
    {
        return true;
    }
    
    override bool IsInventoryItem()
    {
        return false;
    }
    
    override bool CanPutInCargo( EntityAI parent )
    {
        if( !super.CanPutInCargo(parent) ) {return false;}
        return false;
    }

    override bool CanPutIntoHands( EntityAI player )
    {
        if( !super.CanPutIntoHands( parent ) )
        {
            return false;
        }
        return false;
    }
}