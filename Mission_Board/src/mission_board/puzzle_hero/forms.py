from django import forms
from django.core.urlresolvers import reverse_lazy
from django.forms import ValidationError

from crispy_forms.helper import FormHelper
from crispy_forms.layout import Submit

from cs_auth.models import Team

from .models import Flag, Submission, GlobalAnnouncement


class FlagField(forms.CharField):

    def to_python(self, value):
        if not value:
            return ""
        return value

    def validate(self, value):

        super(FlagField, self).validate(value)
        queryset = Flag.objects.filter(token=value).first()

        if not queryset:
            raise ValidationError(
                'Invalid flag: %(value)s',
                code='invalid_flag',
                params={'value': value},
            )


class FlagSubmissionForm(forms.Form):
    token = FlagField(
        max_length=255,
        label="Flag",
        widget=forms.TextInput(
            attrs={'placeholder': 'UQAM{0123456789}'}
        )
    )

    def __init__(self, *args, **kwargs):
        super(FlagSubmissionForm, self).__init__(*args, **kwargs)
        self.helper = FormHelper()
        self.helper.form_action = reverse_lazy('submit_flag')
        self.helper.add_input(Submit('submit', 'Submit'))


class AdminFlagSubmissionForm(forms.Form):
    token = FlagField(
        max_length=255,
        label="Flag",
        widget=forms.TextInput(
            attrs={'placeholder': 'UQAM{0123456789}'}
        )
    )

    team = forms.ModelChoiceField(queryset=Team.objects.all())

    def __init__(self, *args, **kwargs):
        super(AdminFlagSubmissionForm, self).__init__(*args, **kwargs)
        self.helper = FormHelper()
        self.helper.form_action = reverse_lazy('admin_submit_flag')
        self.helper.add_input(Submit('submit', 'Submit'))


class AdminGlobalSubmissionForm(FlagSubmissionForm):

    def __init__(self, *args, **kwargs):
        super(AdminGlobalSubmissionForm, self).__init__(*args, **kwargs)
        self.helper = FormHelper()
        self.helper.form_action = reverse_lazy('admin_global_submit_flag')
        self.helper.add_input(Submit('submit', 'Submit'))


class GlobalAnnouncementForm(forms.ModelForm):
    class Meta:
        model = GlobalAnnouncement
        exclude = []
