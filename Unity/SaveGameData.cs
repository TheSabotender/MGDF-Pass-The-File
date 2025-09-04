using System;
using System.IO;
using UnityEngine;

[Serializable]
public class SaveGameData
{
    public int integer_one;
    public int integer_two;
    public int integer_three;
    public int integer_four;

    public float float_one;
    public float float_two;
    public float float_three;
    public Vector3 vector_one;

    public Vector3 vector_two;

    public static SaveGameData current;
    
    public static void LoadFromFile(string path)
    {
        current = JsonUtility.FromJson<SaveGameData>(File.ReadAllText(path));
    }

    public static void SaveToFile(string path)
    {
        File.WriteAllText(path, JsonUtility.ToJson(current));
    }

    public static bool TryLoadFromArgs()
    {
        var args = Environment.GetCommandLineArgs();
        for (int i = 0; i < args.Length - 1; i++)
        {
            if (string.Equals(args[i], "-load", StringComparison.OrdinalIgnoreCase))
            {
                var filePath = args[i + 1];
                if (string.Equals(Path.GetExtension(filePath), ".mgdf", StringComparison.OrdinalIgnoreCase) && File.Exists(filePath))
                {
                    LoadFromFile(filePath);
                    return true;
                }
                break;
            }
        }
        return false;
    }
}
