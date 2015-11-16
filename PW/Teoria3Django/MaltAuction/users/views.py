from django.shortcuts import render, redirect
from django.views.generic.edit import CreateView, FormView, View, UpdateView
from django.views.generic import RedirectView
from users.models import AuctionUser
from django.core.urlresolvers import reverse, reverse_lazy
from django.contrib.auth.models import Group
from users.forms import RegisterForm
from django.contrib.auth.forms import AuthenticationForm
from django.contrib.auth import login, authenticate, logout
from django.conf import settings
from django.utils.decorators import method_decorator
from django.contrib.auth.decorators import login_required

# Create your views here.

# Register new user
class RegisterUser(CreateView):
    model = AuctionUser    # Put model AND form_class, otherwise a User individual is saved
    form_class = RegisterForm
    # template_name_suffix = '_create_form' # Use for model
    template_name = 'users/create_form.html'
    success_url = reverse_lazy('home:home')
    
    # Modify fields before saving
    def form_valid(self, form):        
        self.object = form.save(commit = False)
        self.object.save()
        self.object.groups.add(Group.objects.get(name = 'customer'))
        return redirect(self.get_success_url())
        # return super(RegisterUser, self).form_valid(form)

# Login User
class LoginUser(FormView):
    model = AuctionUser
    form_class = AuthenticationForm
    template_name = 'users/login_form.html'
    success_url = reverse_lazy('home:home')
    
    def get(self, request, *args, **kwargs):
        if request.user.is_authenticated():
            return redirect(self.get_success_url())
        else:
            return super(LoginUser, self).get(request, *args, **kwargs)
    
    def form_valid(self, form):
        login(self.request, form.get_user())
        return redirect(self.get_success_url())

class LogoutUser(RedirectView):
    url = reverse_lazy('home:home')
    settings.LOGIN_URL = '/users/login/'
    
    @method_decorator(login_required)
    def dispatch(self, *args, **kwargs):
        return super(LogoutUser, self).dispatch(*args, **kwargs)
    
    def get(self, request, *args, **kwargs):
        logout(request)    
        return super(LogoutUser, self).get(request, *args, **kwargs)

class UpdateProfile(UpdateView):
    model = AuctionUser
    fields = ['first_name', 'last_name', 'username', 'email', 'postal_address', 'payment_details']
    readonly_fields = ['username',]
    template_name = 'users/update_form.html'
    success_url = reverse_lazy('home:home')
    settings.LOGIN_URL = '/users/login/'
    
    @method_decorator(login_required)
    def dispatch(self, *args, **kwargs):
        return super(UpdateProfile, self).dispatch(*args, **kwargs)

