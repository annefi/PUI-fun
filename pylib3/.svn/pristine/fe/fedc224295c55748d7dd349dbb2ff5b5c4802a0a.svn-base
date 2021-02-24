"""
Date: 28.1.2015
authour: <drews@physik.uni-kiel.de>, <berger@physik.uni-kiel.de>
"""

import unittest
from pylib3.dbData._dbData import dbData
#from numpy import arange, meshgrid, ndarray, max, min, equal, random, argwhere, alltrue, array, zeros
from numpy import *
import matplotlib
import os
import sys


class NullDevice():

    def write(self, s):
        pass

    def flush(self):
        pass

orig_stdout = sys.stdout


class mydbData(dbData):

    """
    DbData class for Testing purposes
    """

    def load_data(self):
        Data1 = arange(1e4)
        Data2, Data3 = meshgrid(arange(100), arange(100))
        Data2 = Data2.flatten()
        Data3 = Data3.flatten()
        self.data["D1"] = Data1
        self.data["D2"] = Data2
        self.data["D3"] = Data3
        self.data["I"] = random.randint(0, 1000, len(Data2))


def test_op(datadict, key, value):
    return equal(datadict[key], value)


class dbData_CoreTest(unittest.TestCase):

    """
    Test of all dbData Methods
    """

    def setUp(self):
        """
        Sets up the Test
        """
        self.db = mydbData()
        self.db.set_mask("Master", "D1", 160, op="<")
        self.db.add_mask("M1")
        self.db.set_mask("M1", "D1", 1500, op="<")
        self.db.add_mask("M2")
        self.db.set_mask("M2", "D1", 150, op=">")
        self.db.set_mask("M2", "D2", 50, op="<")
        self.db.add_mask("M3")
        self.db.set_mask("M3", "D2", 60, op="<")
        sys.stdout = NullDevice()

    def tearDown(self):
        """
        Called after each test
        """
        self.db = None
        sys.stdout = orig_stdout

    def testAddMask(self):
        """ Routine to check dbData add_mask routine """
        self.db.add_mask("Test 1")
        self.db.add_mask(["Test_2", "Test3"])
        for T in ["Test 1", "Test_2", "Test3"]:
            assert T in self.db.mask.keys(), T + " was not added to db.masks"
            assert T in self.db.mp.keys(), T + \
                " was not added to db.mp (mask properties)"
            assert len(unique([self.db.mp[K].get("color") for K in self.db.mp.keys()])) == len(self.db.mask.keys()), \
                "Masks don't have a unique color"

    def testRemoveMask(self):
        """ Routine to check dbData remove_mask routine """
        self.db.add_mask(["Test1", "Test2", "Test3", "Test4"])
        self.db.remove_mask("Test1")
        self.db.remove_mask(["Test3", "Test4"])
        for T in ["Test1", "Test3", "Test4"]:
            assert T not in self.db.mask.keys(
            ), T + " was not removed db.masks"
            assert T not in self.db.mp.keys(), T + \
                " was not removed db.mp (mask properties)"

    def testAddData(self):
        """ Routine to check dbData add_data method"""
        newData = self.db.data["D1"]
        self.db.add_data("D4", newData)
        assert alltrue(
            self.db.data["D4"] == self.db.data["D1"]), "Added Data is corrupted"
        assert "D4" in self.db.dp.keys(
        ), "Data was not added to the data properties dict db.pd"

    def testGetData(self):
        """ Routine to test the get_data method"""
        data = self.db.get_data("Master", "D1")
        data2 = self.db.get_data("M1", "D1")
        assert isinstance(data, ndarray), "Returned data has the wrong type"
        assert alltrue(
            arange(160) == data), "Returned data has the wrong entries"
        assert alltrue(
            data2 < 1500), "Returned Data has been incorrectly filtered by mask"

    def testGetMask(self):
        """ Routine to test the get_mask method"""
        self.db.add_mask("Test")
        self.db.set_mask("Test", "D1", 60, op="<")
        self.db.add_mask("Test2")
        self.db.set_mask("Test2", "D1", 40, op="<")
        ma = self.db.get_mask("Master")
        ma2 = self.db.get_mask("Test")
        ma3 = self.db.get_mask(["Test", "Test2"])
        assert len(ma) == len(
            ma2), "Different array length for different masks"
        assert sum(ma2) == 60, "Returned bool array of Mask is corrupted"
        assert sum(ma3) == 40, "Returned bool array of Mask List is corrupted"

    def testDM(self):
        """Tests the DM method of dbData"""
        self.db.set_mask("Master", "D1", 110, op="<")
        ma = self.db.DM()
        assert sum(
            ma) == 160, "Returned bool array of Master Mask is corrupted"

        assert alltrue(ma == self.db.get_mask("Master")), \
            "DM() returns different bool array than get_mask('Master')"

    def testSetDataProperty(self):
        """ Routine to test the set_data_property method """
        self.db.set_data_property("D1", "color", "yellow")
        assert self.db.dp["D1"].get("color") == "yellow", \
            "Data property is set incorrectly for specific data product"

        self.db.set_data_property("all", "color", "red")
        assert self.db.dp["D2"].get("color") == "red", \
            "Data property is set incorrectly with arg 'all'"

    def testSetMaskProperty(self):
        """ Routine to test the set_mask_property method """
        self.db.set_mask_property("M1", "color", "yellow")
        assert self.db.mp["M1"].get("color") == "yellow",  \
            "Mask property is set incorrectly for specific mask"

        self.db.set_mask_property("all", "color", "red")
        assert self.db.mp["M3"].get("color") == "red", \
            "Data property is set incorrectly with arg 'all'"

    def testSetGlobalProperty(self):
        """ Routine to test the set_global_property method """
        self.db.set_global_property("xtick.color", "red")
        assert matplotlib.rcParams[
            "xtick.color"] == "red", "Global parameters were set incorrectly"

    def testAddReducedData(self):
        """ Routine to test the set_global_property method """

        D4 = array([1, 2])
        D5 = array([0, -999])
        expandarray = zeros(self.db.data["D3"].shape, dtype=int32) + 1
        self.db.add_reduced_data("D4", D4, "EXPK", expansion=expandarray)
        self.db.add_reduced_data("D5", D5, "EXPK")
        assert alltrue(self.db.data["D4"] == 2), \
            "Reduced Data with given Expansionarray did not return the expected data values"

        assert alltrue(self.db.data["D5"] == -999), \
            "Reduced Data without given Expansionarray did not return the expected data values"

        assert len(unique([self.db.dp[key].get("color") for key in self.db.dp.keys()])) == 6, \
            "Added Data Products have the same color properties"

    def testCopyMask(self):
        """ Routine to test the copy_mask method """
        self.db.copy_mask("M1b", "M1")
        assert alltrue(self.db.get_mask("M1b") == self.db.get_mask("M1")), \
            "Bool Array of copied mask differs from original"

        assert self.db.mp["M1b"].get("color") != self.db.mp["M1"].get("color"), \
            "Copied Mask has the same color property"

        self.db.copy_mask("M3b", "M3")
        assert self.db.mask["M3b"].appliedmasks == self.db.mask["M3"].appliedmasks, \
            "Applieds Masks list is not copied correctly"

        assert alltrue(self.db.get_mask("M3b") == self.db.get_mask("M3")), \
            "Bool Array of copied mask differs from original with an appliedmask "

    def testRemoveMask(self):
        """ Routine to test the remove_mask method """
        self.db.remove_mask("M1")
        assert "M1" not in self.db.mask.keys(), "Mask not properly removed"
        assert "M1" not in self.db.mp.keys(
        ), "Mask Property not properly removed"

        self.db.remove_mask("all")
        assert "M3" not in self.db.mask.keys(
        ), "Mask not properly removed using arg 'all'"
        assert "M2" not in self.db.mp.keys(
        ), "Mask Property not properly removed using arg 'all'"

    def testRemoveSubMask(self):
        """ Routine to test the remove_submask method"""
        ma1 = self.db.get_mask("M2")
        self.db.remove_submask("M2", "D2")
        ma2 = self.db.get_mask("M2")
        self.db.remove_submask("M2", "D1")
        ma3 = self.db.get_mask("M2")
        data = self.db.get_data("M2", "D2")
        assert len(unique(data)) == 100, "Submask was not removed properly"
        assert not alltrue(ma1 == ma2), "Submask was not removed properly"
        assert not alltrue(ma3 == ma2), "Submask was not removed properly"

        self.db.remove_submask("Master", "D1")
        data = self.db.get_data("M2", "D1")
        assert max(data) == 9999, "Submask was not removed properly"

    def testRemoveAppliedMask(self):
        """ Routine to test the remove_appliedmask method"""
        self.db.set_mask("M3", "M2", applied=True)
        ma1 = self.db.get_mask("M3")
        self.db.remove_appliedmask("M3", "M2")
        ma2 = self.db.get_mask("M3")
        assert "M2" not in self.db.mask[
            "M3"].appliedmasks, "Applied mask was not removed"
        assert not alltrue(ma1 == ma2), "Applied mask was incorrectly removed"
        assert max(self.db.get_data("M3", "D1")
                   ) > 150, "Applied mask incorrectly removed"

    def testRemoveDirectMask(self):
        """ Routine to test the remove_directmask method"""
        self.db.reset_mask("Master")
        dm = zeros((self.db.data["D1"].shape), dtype=bool)
        dm[0:2] = True
        self.db.set_mask("Master", "Test", dm, direct=True)
        self.db.remove_directmask("Master", "Test")

        assert not self.db.mask["Master"].directmasks.has_key("Test"), \
            "Direct mask still in directmask dictionary of Mask class"

        assert alltrue(self.db.mask["Master"].ma), \
            "Direct Mask incorrectly applied"

    def testResetMask(self):
        """ Routine to test the reset_mask method """
        self.db.reset_mask("M2")
        assert alltrue(self.db.mask["M2"].ma == self.db.mask["Master"].ma), \
            "Reset Mask doesnt work properly for added masks"

        self.db.reset_mask("Master")
        assert alltrue(self.db.mask["Master"].ma), \
            "Reset Mask doesnt work properly for Master Mask"

        self.db.set_mask("M2", "D1", 15, 15)
        self.db.set_mask("M3", "M2", applied=True)
        self.db.set_mask("M3", "D2", 10, 20)
        self.db.set_mask("M3", "D2", 15, 30)
        self.db.set_mask("M3", "D3", 1, 1)
        dm = zeros((self.db.data["D1"].shape), dtype=bool)
        dm[0:2] = True
        self.db.set_mask("M3", "Test", dm, direct=True)
        self.db.reset_mask("M3")

        assert not 'Test' in list(self.db.mask["M3"].directmasks.keys()), \
            "Direct mask still in directmask dictionary of after reset_mask"

        assert "M2" not in self.db.mask["M3"].appliedmasks, \
            "Applied mask was not removed after reset_mask"

        assert len(self.db.mask["M3"].submasks.keys()) == 0,\
            " Submasks not removed after reset_mask "

        assert alltrue(self.db.mask["M3"].ma), \
            " Reset Mask doesnt work properly for added mask after adding several \
		sub, applied, and direct masks"

    def testSetMaskSS(self):
        """ Routine to test set_mask method with standard (submask setting) behaviour"""
        self.db.add_mask("M4")
        self.db.reset_mask("Master")
        self.db.set_mask("M4", "D1", 15, 15)

        assert argwhere(self.db.mask["M4"].ma)[0, 0] == 15, \
            "Submask Setting failed in set_mask with op='between'"

        self.db.set_mask("M4", "D1", 16, op="==")
        assert alltrue(argwhere(self.db.mask["M4"].ma).flatten() == array([15, 16])), \
            "Submask Setting failed in set_mask with op='=='"

        self.db.set_mask("M4", "D1", 16, op=">")
        assert alltrue(argwhere(self.db.mask["M4"].ma).flatten() == arange(15, 1e4)), \
            "Submask Setting failed in set_mask with op='>'"

        self.db.set_mask("M4", "D1", 15, 15, reset=True)
        assert argwhere(self.db.mask["M4"].ma)[0, 0] == 15, \
            "Submask Setting failed with 'reset=True'"

    def testSetMaskUS(self):
        """ Routine to test set_mask method with user defined operator"""
        self.db.add_mask("M4")
        self.db.reset_mask("Master")
        self.db.set_mask("M4", "D1", 15, op=test_op, set_custom_prod="D1")

        assert argwhere(self.db.mask["M4"].ma)[0, 0] == 15, \
            "Submask Setting failed in set_mask with user defined operator"

        self.db.set_mask("M4", "D1", -1, 1e9, reset=True)
        assert alltrue(self.db.mask["M4"].ma), \
            "User Defined operator not resetted with 'reset=True'"

    def testSetMaskDM(self):
        """ Routine to test set_mask method with direct mask"""
        self.db.add_mask("M4")
        self.db.reset_mask("Master")
        dm = zeros((self.db.data["D1"].shape), dtype=bool)
        dm[0:2] = True

        self.db.set_mask("M4", "D1", dm, direct=True)
        assert alltrue(self.db.get_data("M4", "D1") == array([0, 1])), \
            "Direct Mask was not properly set"

    def testSetMaskAM(self):
        """ Routine to test set_mask method with applied mask"""
        self.db.add_mask("M4")
        self.db.set_mask("M4", "M2", applied=True)

        assert alltrue(self.db.mask["M4"].ma == self.db.mask["M2"].ma),\
            " Applied Mask was not properly applied"

    def testSaveAll(self):
        """ Routine to test the save_all method """
        self.db.save_all("foo.bar", overwrite=True)

        assert os.path.isfile("foo.bar"),\
            "Nothing was saved with save_all method"
        os.remove("foo.bar")

    def testSaveMask(self):
        """ Routine to test the save_masks method """
        self.db.save_masks("foo.bar", overwrite=True)

        assert os.path.isfile("foo.bar"),\
            "Nothing was saved with save_mask method"
        os.remove("foo.bar")

    def testLoadMasks(self):
        """ Routine to test the load_masks method """

        self.db.save_masks("foo.bar", overwrite=True)
        ma = self.db.mask["Master"].ma
        ma1 = self.db.mask["M1"].ma
        ma2 = self.db.mask["M2"].ma
        ma3 = self.db.mask["M3"].ma
        c1 = self.db.mp["M1"].get("color")
        c2 = self.db.mp["M2"].get("color")
        c3 = self.db.mp["M3"].get("color")
        self.db.remove_mask("all")
        self.db.reset_mask("all")
        self.db.load_masks("foo.bar")

        for m in self.db.mask:
            self.db.mask[m].calc_mask()

        assert "M1" in self.db.mask.keys(), "Mask was not loaded"
        assert "M2" in self.db.mask.keys(), "Mask was not loaded"
        assert "M3" in self.db.mask.keys(), "Mask was not loaded"

        assert alltrue(max(self.db.get_data("M1", "D1")) == 1499),\
            " Loaded Mask is not the same as original one"

        assert alltrue(max(self.db.get_data("M2", "D2")) == 49),\
            " Loaded Mask is not the same as original one"

        assert alltrue(max(self.db.get_data("M3", "D2")) == 59),\
            " Loaded Mask is not the same as original one"

    def testAddSubset(self):
        """ Routine to test the add_subset method"""
        assert 1 / 0, "Test needs to be implemented"

    def testLoadSubset(self):
        """ Routine to test the load_subset method"""
        assert 1 / 0, "Test needs to be implemented"

    def testSaveSubset(self):
        """ Routine to test the save_subset method"""
        assert 1 / 0, "Test needs to be implemented"

    def testSetMask1D(self):
        """ Routine to test the set_mask1D method"""
        assert 1 / 0, "Test needs to be implemented"

    def testSetMask2D(self):
        """ Routine to test the set_mask2D method"""
        assert 1 / 0, "Test needs to be implemented"

    def testReadHeader(self):
        """ Routine to test the read_header method"""
        assert 1 / 0, "Test needs to be implemented"

    def testShowMask(self):
        """ Routine to test wheather show_mask is still running """
        self.db.show_mask()

    def testHist1D(self):
        """ Routine to test wheather show_mask is still running """
        self.db.reset_mask("Master")
        self.db.hist1d("D2", binx=arange(0, 101, 1), weights="D1", Master=True,
                       xlabel="TESTX", ylabel="TESTY", smask=["M1", "M3", "M2"], norm="ysum")

    def testHist2D(self):
        """ Routine to test wheather show_mask is still running """
        self.db.reset_mask("Master")
        self.db.hist2d("D2", "D3", weights="I", binx=arange(0, 151, 1), biny=arange(
            0, 101, 1), cb="TestC", ncols=2, xlabel="TESTX", ylabel="TESTY", shade=True, clines=2)

    def testTimeseries(self):
        """ Routine to test animate1d method """
        self.db.reset_mask("Master")
        self.db.timeseries("D2", prodx="D1")

    def testAnimate1D(self):
        """ Routine to test animate1d method """
        self.db.reset_mask("Master")
        self.db.animate1d("D2", "D3", binx=arange(0, 101, 1),
                          binz=arange(0, 101, 10), weights="I", Master=False)

    def testAnimate2D(self):
        """ Routine to test wheather show_mask is still running """
        self.db.reset_mask("Master")
        self.db.animate2d("D2", "D3", "D2", binx=arange(0, 101, 1),
                          biny=arange(0, 101, 1), binz=arange(0, 100, 10), weights="I")

    def testQuicklook(self):
        """ Routine to test the quicklook method"""
        self.db.quicklook()
if __name__ == "__main__":
    suiteCORE = unittest.makeSuite(dbData_CoreTest, 'test')
    unittest.TextTestRunner().run(suiteCORE)
