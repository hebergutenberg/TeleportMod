class JsonConfigManager
{
    // Method for loading config
    static ref LO_TeleportConfig LoadTeleportConfig()
    {
        string error;
        ref LO_TeleportConfig config = new LO_TeleportConfig();

        // Create TeleportMod directory if it doesn't exist
        string configDirPath = "$profile:TeleportMod";
        if (!FileExist(configDirPath))
        {
            MakeDirectory(configDirPath);
            Print("Created TeleportMod directory: " + configDirPath);
        }

        string configFilePath = "$profile:TeleportMod/TeleportModConfig.json";  // Updated path
        if (FileExist(configFilePath))
        {
            // Reading JSON file content
            string jsonContent;
            string line;
            FileHandle file = OpenFile(configFilePath, FileMode.READ);
            if (file != -1)  // Check for successful file opening
            {
                while (FGets(file, line) > 0)  // Reading file content
                {
                    // Lines are added to jsonContent
                    jsonContent += line;
                }
                CloseFile(file);  // Close file

                // JSON deserialization to object
                JsonSerializer json = new JsonSerializer();
                json.ReadFromString(config, jsonContent, error);  // Deserialize string to object
            }
            else
            {
                Print("Failed to open the JSON config file!");
                Print(error);
            }
        }
        else
        {
            // If config not found, create new one
            CreateDefaultConfig();
            return LoadTeleportConfig();  // Load config after creating it
        }

        return config;
    }

    // Method for creating default config
    static void CreateDefaultConfig()
    {
        ref LO_TeleportConfig defaultConfig = new LO_TeleportConfig();

        // Example default data for teleport
        LO_TeleportEntry entry1 = new LO_TeleportEntry();
        entry1.EnableTeleport = true;
        entry1.TeleportName = "Teleport 1";
        entry1.ObjectType = "Land_Door_germa_1";
        entry1.ObjectCoordinates = { 7758.640137, 16.184601, 14116.900391 };
        entry1.TeleportPosition = { 10.299805, 10.765999, 10.270020 };
        entry1.CheckRadius = 1.0;
        entry1.RequiredItem = "Crowbar";
        entry1.RequiredItemDamagePercent = 50;  // 50% damage per use
        entry1.ConsumeRequiredItem = false;     // Don't consume item (just damage it)
        entry1.TeleportActiveTimeSeconds = 30;
        entry1.MissingItemMessage = "You need a Crowbar to open the barn!";
        // Sound configuration
        entry1.EnableTeleportSound = true;
        entry1.TeleportSoundFile = "TeleportMod\\Data\\teleport_sound.ogg";
        entry1.TeleportSoundRadius = 50.0;  // 50 meter radius
        entry1.TeleportSoundVolume = 1.0;   // 100% volume
        defaultConfig.TeleportEntries.Insert(entry1);

        LO_TeleportEntry entry2 = new LO_TeleportEntry();
        entry2.EnableTeleport = false;
        entry2.TeleportName = "Teleport 2";
        entry2.ObjectType = "Land_House_1W01";
        entry2.ObjectCoordinates = { 1250.0, 15.0, 1350.0 };
        entry2.TeleportPosition = { 1300.0, 20.0, 1400.0 };
        entry2.CheckRadius = 2.5;
        entry2.RequiredItem = "Shovel";
        entry2.RequiredItemDamagePercent = 0;   // No damage
        entry2.ConsumeRequiredItem = true;      // Consume/destroy item after use
        entry2.TeleportActiveTimeSeconds = 0;
        entry2.MissingItemMessage = "A Shovel is required to interact with this house!";
        // Sound configuration
        entry2.EnableTeleportSound = true;
        entry2.TeleportSoundFile = "TeleportMod\\Data\\teleport_sound.ogg";
        entry2.TeleportSoundRadius = 30.0;  // 30 meter radius
        entry2.TeleportSoundVolume = 0.8;   // 80% volume
        defaultConfig.TeleportEntries.Insert(entry2);

        // Serialize data to JSON string
        string jsonContent;
        JsonSerializer json = new JsonSerializer();
        json.WriteToString(defaultConfig, true, jsonContent);  // Convert data to string

        // Create TeleportMod directory if it doesn't exist
        string configDirPath = "$profile:TeleportMod";
        if (!FileExist(configDirPath))
        {
            MakeDirectory(configDirPath);
        }

        string configFilePath = "$profile:TeleportMod/TeleportModConfig.json";  // Updated file path
        FileHandle file = OpenFile(configFilePath, FileMode.WRITE);
        if (file != -1)  // Check for successful file opening
        {
            FPrint(file, jsonContent);  // Write to file
            CloseFile(file);  // Close file
            Print("Default teleport config created at: " + configFilePath);
        }
        else
        {
            Print("Failed to create default teleport config!");
        }
    }

    static void SpawnTeleportPoints() {
        LO_TeleportConfig m_TeleportConfig = LoadTeleportConfig();
        foreach (ref LO_TeleportEntry entry : m_TeleportConfig.TeleportEntries)
        {
            if (entry.EnableTeleport)
            {
                // Spawn object for interaction
                TeleportHelper.CreateTeleportInteractionObject(entry.ObjectType, entry.ObjectCoordinates, entry.ObjectOrientation);
            }
        }
    }
}